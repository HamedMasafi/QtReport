/***************************************************************************
 *   QtReport                                                              *
 *   Qt Report Builder Solution                                            *
 *                                                                         *
 *   Copyright (C) 2010 by Hamed Masafi                                    *
 *   Hamed.Masafi@GMail.COM                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "qreportdocumentdesigner.h"

#include <QDebug>
#include <QFile>
#include <QList>
#include <QMetaProperty>
#include <QMetaClassInfo>
#include <QApplication>
#include <QClipboard>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QMenu>
#include <QMouseEvent>
#include <QPageSetupDialog>
#include <QPrinter>
#include <QScreen>
#include <QScrollBar>
#include <QWidget>
#include <QUndoStack>
#include <QDesktopWidget>
#include <QDomDocument>
#include <QMessageBox>
#include <qmath.h>
#include <qreportdataconnection.h>
#include <qreportparametere.h>

#include "qreport.h"
#include "qreportevent.h"
#include "qreportdocumentview.h"
#include "qreportruler.h"
#include "qreportdocpage.h"
#include "qreportwidgetbase.h"
#include "qreportwidgetresizer_p.h"
#include "qreportband.h"
#include "qreportscene.h"
#include "qreportpropertydialog.h"
#include "qreportpropertypagetext.h"
#include "qreportpropertypagefont.h"
#include "qreportpropertypageimage.h"
#include "qreportpropertypagelinetype.h"
#include "qreportpropertypagealign.h"
#include "qreportpropertypagerectangle.h"
#include "qreportpropertypageformat.h"
#include "qreportpropertypagewidget.h"
#include "qreportundocommands.h"
#include "qreporttextbox.h"
#include "qreportdatabaseinfodialog.h"
#include "qreportparameteredialog.h"
#include "qreportdatatabledialog.h"
#include "qreportpropertyband.h"
#include "qreportpropertysort.h"
#include "qreportpropertyfilter.h"
#include "qreportscene.h"

LEAF_BEGIN_NAMESPACE

bool lessThan(const QReportBand *x1, const QReportBand *x2)
{
    if(x1->bandType() == x2->bandType())
        return x1->index() < x2->index();
    else
        return x1->bandType() < x2->bandType();
}


class QReportDocumentDesignerPrivate
{
public:
    QReportDocumentDesignerPrivate(QReportDocumentDesigner *parent):
        activeWidget(0),
        activeBand(0),
        zoom(100),
        q_ptr(parent),
        readyToPaste(false)
    {}

    QReport*                report;
    QGridLayout*            gridLayout;
    QReportRuler*           vRuler;
    QReportRuler*           hRuler;
    QReportDocumentView*    document;
    QList<QReportPage*>     pages;

//    QSizeF                  designArea;
    QReportWidgetBase*      activeWidget;
    QReportBand*            activeBand;

    QReportScene*           scene;
    QReportWidgetResizer*   resizer;
    QUndoStack*             undoStack;

    int                     zoom;
    qreal                   gridSize;
    bool                    alignToGrid;
    QReportPage*            pageOne;

    bool                    readyToPaste;       // is scene force to place content on next mouse down
    bool                    pasteInRect;        // paste is in rect or in point
    QString                 pasteBoard;         // content of clipboard
    QPointF                 lastScenePoint;     // last clicked position on scene
    QRectF                  pasteRect;          // rectangle that new widget must place
    QGraphicsRectItem*      pasteRectItem;      // paste rect item
    ResizeDirection         pasteDirection;     // direction of new widget such as line or rect
    QPointF                 pasteMargin;        // margin (for line)

    QString                 lastXML;            // hold last xml for undo stack
    QString                 lastBandXML;

    void applyConnectionsXml(QDomElement oldElement, QDomElement newElement);
    void applyDataTablesXml(QDomElement oldElement, QDomElement newElement);
    void applyBandsXml(QDomElement oldElement, QDomElement newElement);
    void applyWidgetsXml(QDomElement oldElement, QDomElement newElement);
    void applyParameteresXml(QDomElement oldElement, QDomElement newElement);

    void addWidget(QReportWidgetBase *widget);
    void addBand(QReportBand *band);

    void removeWidget(QReportWidgetBase *widget);
    void removeBand(QReportBand *band);

private:
    QReportDocumentDesigner  *const q_ptr;
    Q_DECLARE_PUBLIC(QReportDocumentDesigner)

};

void QReportDocumentDesignerPrivate::applyConnectionsXml(QDomElement oldElement, QDomElement newElement)
{
    Q_Q(QReportDocumentDesigner);

    QStringList oldNames, newNames;

    QDomNodeList oldNodes = oldElement.elementsByTagName(XML_NODE_CONNECTION);
    QDomNodeList newNodes = newElement.elementsByTagName(XML_NODE_CONNECTION);

    for(int i = 0; i < oldNodes.count(); i++)
        oldNames << oldNodes.at(i).toElement().attribute("objectName");

    for(int i = 0; i < newNodes.count(); i++){
        QDomElement el = newNodes.at(i).toElement();
        QString elementName = el.attribute("objectName");
        newNames << elementName;

        if(oldNames.contains(elementName)){
            QReportDataConnection *conn = report->findConnectionByName(elementName);
            conn->loadDom(&el);
        }else{
            QReportDataConnection *conn = new QReportDataConnection();
            report->addConnection(conn);
            conn->loadDom(&el);
        }//if
    }//for

    foreach (QString oldElementName, oldNames)
        if(!newNames.contains(oldElementName))
            report->removeConnection(report->findConnectionByName(oldElementName));
}

void QReportDocumentDesignerPrivate::applyDataTablesXml(QDomElement oldElement, QDomElement newElement)
{
    Q_Q(QReportDocumentDesigner);

    QStringList oldNames, newNames;

    QDomNodeList oldNodes = oldElement.elementsByTagName(XML_NODE_DATATABLE);
    QDomNodeList newNodes = newElement.elementsByTagName(XML_NODE_DATATABLE);

    for(int i = 0; i < oldNodes.count(); i++)
        oldNames << oldNodes.at(i).toElement().attribute("objectName");

    for(int i = 0; i < newNodes.count(); i++){
        QDomElement el = newNodes.at(i).toElement();
        QString elementName = el.attribute("objectName");
        newNames << elementName;

        if(oldNames.contains(elementName)){
            QReportDataTable *param = report->dataTable(elementName);
            param->loadDom(&el);
        }else{
            QReportDataTable *param = new QReportDataTable(el.attribute("connectionName"));
            report->addDataTable(param);
            param->loadDom(&el);
        }//if
    }//for

    foreach (QString oldElementName, oldNames)
        if(!newNames.contains(oldElementName))
            report->removeDataTable(report->dataTable(oldElementName));
}


void QReportDocumentDesignerPrivate::applyBandsXml(QDomElement oldElement, QDomElement newElement)
{
    Q_Q(QReportDocumentDesigner);

    QStringList oldNames, newNames;

    QDomNodeList oldNodes = oldElement.elementsByTagName(XML_NODE_BAND);
    QDomNodeList newNodes = newElement.elementsByTagName(XML_NODE_BAND);

    for(int i = 0; i < oldNodes.count(); i++)
        oldNames << oldNodes.at(i).toElement().attribute("objectName");

    for(int i = 0; i < newNodes.count(); i++){
        QDomElement el = newNodes.at(i).toElement();
        QString elementName = el.attribute("objectName");
        newNames << elementName;

        if(oldNames.contains(elementName)){
            QReportBand *band = report->findBandByName(elementName);
            band->loadDom(&el);
        }else{
            QReportBand *band = new QReportBand();
            addBand(band);
            band->loadDom(&el);
        }//if
    }//for

    foreach (QString oldElementName, oldNames)
        if(!newNames.contains(oldElementName))
            removeBand(report->findBandByName(oldElementName));

    q->reorderBands();
}

void QReportDocumentDesignerPrivate::applyWidgetsXml(QDomElement oldElement, QDomElement newElement)
{
    Q_Q(QReportDocumentDesigner);

    QStringList oldNames, newNames;

    QDomNodeList oldNodes = oldElement.elementsByTagName(XML_NODE_WIDGET);
    QDomNodeList newNodes = newElement.elementsByTagName(XML_NODE_WIDGET);
    for(int i = 0; i < oldNodes.count(); i++)
        oldNames << oldNodes.at(i).toElement().attribute("objectName");

    for(int i = 0; i < newNodes.count(); i++){
        QDomElement el = newNodes.at(i).toElement();
        QString elementName = el.attribute("objectName");
        newNames << elementName;

        if(oldNames.contains(elementName)){
            QReportWidgetBase *widget = report->findWidgetByName(elementName);
            widget->loadDom(&el);
            widget->update();

            q->refreshWidgetParents(widget);
            resizer->addWidget(widget);
        }else{
            resizer->addWidget(q->createWidgetsFromDom(el));
        }//if
    }//for

    resizer->refresh();

    foreach (QString oldElementName, oldNames)
        if(!newNames.contains(oldElementName))
            q->removeReportWidget(report->findWidgetByName(oldElementName));
}

void QReportDocumentDesignerPrivate::applyParameteresXml(QDomElement oldElement, QDomElement newElement)
{
    Q_Q(QReportDocumentDesigner);

    QStringList oldNames, newNames;

    QDomNodeList oldNodes = oldElement.elementsByTagName(XML_NODE_PARAMETER);
    QDomNodeList newNodes = newElement.elementsByTagName(XML_NODE_PARAMETER);

    for(int i = 0; i < oldNodes.count(); i++)
        oldNames << oldNodes.at(i).toElement().attribute("objectName");

    for(int i = 0; i < newNodes.count(); i++){
        QDomElement el = newNodes.at(i).toElement();
        QString elementName = el.attribute("objectName");
        newNames << elementName;

        if(oldNames.contains(elementName)){
            QReportParametere *param = report->parameter(elementName);
            param->loadDom(&el);
        }else{
            QReportParametere *param = new QReportParametere();
            report->addParametere(param);
            param->loadDom(&el);
        }//if
    }//for

    foreach (QString oldElementName, oldNames)
        if(!newNames.contains(oldElementName))
            report->removeParametere(report->parameter(oldElementName));
}

void QReportDocumentDesignerPrivate::addBand(QReportBand *band)
{
    Q_Q(QReportDocumentDesigner);

//    band->setPos(report->marginLeft(), report->marginTop());
//    band->setWidth(designArea.width() - 1);

    band->setParentItem(pages[ 0 ]);

    q->connect(band, SIGNAL(selectedChanged()),
            q,   SLOT(reportWidget_selectedChanged()));

    q->connect(band, SIGNAL(resizing(QReportResizeEvent*)),
            q,   SLOT(reportWidget_resizing(QReportResizeEvent*)));

    q->connect(band, SIGNAL(contextMenu()),
            q,   SLOT(reportWidget_contextMenu()));


    activeBand = band;
    report->bandToFront(activeBand);

    band->setObjectName(q->getFreeSectionName(band->typeString()));
    report->bands()->append(band);

    q->reorderBands(true);
    resizer->setActiveItem(band);
    activeWidget = band;
}

void QReportDocumentDesignerPrivate::removeWidget(QReportWidgetBase *widget)
{
//    for (int i = 0; i < report->widgets()->count(); i++)
//        if (report->widgets()->at(i)->objectName() == widget->objectName())
//            report->widgets()->removeAt(i);

    report->removeWidget(widget->objectName());
    scene->removeItem(widget);
}

void QReportDocumentDesignerPrivate::removeBand(QReportBand *band)
{
//    if(!band) return;

//    for(int i = 0; i < report->bands()->count(); i++)
//        if(report->bands()->at(i)->objectName() == band->objectName())
//            report->bands()->removeAt(i);

    report->removeBand(band->objectName());
    scene->removeItem(band);
}



/*!
  \class QReportDocumentDesigner

  Define a new document designet widget.
  A document designer contain \e QReportDocument and two \e QReportRuler (vertical & horzontal).

*/

/*!
  Create a new QReportDocumentDesigner class, this constructor implements
  QWidget constructor.
  \param parent parent of widget
  \param f flags for widget
 */
QReportDocumentDesigner::QReportDocumentDesigner(QWidget *parent, QReport *report) :
    QWidget(parent),
    d_ptr(new QReportDocumentDesignerPrivate(this))
{
    Q_D(QReportDocumentDesigner);
    QSizeF pageSize;

    setObjectName("documentDesigner");

    // gridLayout
    d->gridLayout = new QGridLayout(this);
    d->gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    d->gridLayout->setSpacing(0);

    // d->hRuler
    d->hRuler = new QReportRuler(this, Qt::Horizontal);
    d->hRuler->setObjectName("d->hRuler");
    d->hRuler->setMinimumHeight(14);
    d->gridLayout->addWidget(d->hRuler, 0, 1, 1, 1);
    d->hRuler->setPixelPerUnit(96);

    // d->vRuler
    d->vRuler = new QReportRuler(this, Qt::Vertical);
    d->vRuler->setObjectName("d->vRuler");
    d->vRuler->setMinimumWidth(14);
    d->gridLayout->addWidget(d->vRuler, 1, 0, 1, 1);
    d->vRuler->setPixelPerUnit(96);

    // scene
    d->scene = new QReportScene;
    d->scene->setObjectName(QString::fromUtf8("scene"));
    d->scene->setParent(this);
    d->scene->setBackgroundBrush(Qt::gray);

    d->pasteRectItem = d->scene->addRect(0, 0, 0, 0);
    d->pasteRectItem->setVisible(false);
    d->pasteRectItem->setPen(QPen(Qt::blue));
//    d->pasteRectItem->setBrush(QBrush(Qt::yellow));

    d->undoStack = new QUndoStack(this);
    d->undoStack->setObjectName(QString::fromUtf8("undoStack"));

    connect(d->scene, SIGNAL(selectionChanged()),
            this, SLOT(on_scene_selectionChanged()));

    // report
    d->report = report;
    d->report->setObjectName("Report");


    // document
    d->document = new QReportDocumentView(d->scene, this);
    d->document->setObjectName(QString::fromUtf8("document"));
    d->document->setCacheMode(QGraphicsView::CacheNone);
    d->document->setDragMode(QGraphicsView::RubberBandDrag);
    d->gridLayout->addWidget(d->document, 1, 1, 1, 1);


    // resizer
    d->resizer = new QReportWidgetResizer(d->scene);
    d->resizer->setParent(this);
    d->resizer->setObjectName("resizer");

    /*
       connect( resizer,  SIGNAL(pointGridNeeded( QReportMoveEvent* )),
                this,     SLOT(on_resizer_pointGridNeeded(QReportMoveEvent*))  );
       connect( resizer,  SIGNAL(sizeGridNeeded( RResizeEvent* )),
                this,     SLOT(on_resizer_sizeGridNeeded(RResizeEvent*)) );
  */

    d->gridSize = 15;
    d->alignToGrid = true;
    d->report->setMargins(60, 60, 60, 60);

    pageSize = QSizeF(795, 1122);
    d->report->setSize(pageSize);
//    d->designArea = QSizeF(pageSize.width() - d->report->marginLeft() - d->report->marginRight(),
//                           pageSize.height() - d->report->marginTop() - d->report->marginBottom());

    // Create new default one page
    d->pageOne = new QReportPage;
    d->pageOne->setSize(d->report->pageSize().width(),
                        d->report->pageSize().height());
    d->pageOne->setGridType(::DotGrid);
    d->scene->addItem(d->pageOne);
    d->pages.append(d->pageOne);
    d->pageOne->setMargins(d->report->marginLeft(), d->report->marginTop(), d->report->marginRight(), d->report->marginBottom());
    d->pageOne->setGridSize(d->gridSize);
    d->activeWidget = d->pageOne;

    connect(d->pageOne,  SIGNAL(selectedChanged()) ,
            this,     SLOT(reportWidget_selectedChanged()));
    connect(d->pageOne, SIGNAL(contextMenu()),
            this,   SLOT(reportWidget_contextMenu()));

    connect(d->resizer, SIGNAL(resized()),
            this,     SLOT(reportWidget_resized()));

    QMetaObject::connectSlotsByName(this);
    setSceneRect();
    updateScrollBars();
}


QReportDocumentDesigner::~QReportDocumentDesigner()
{
}

//-- widget management -------------------------------------------------------------------

void QReportDocumentDesigner::addReportWidget(QReportWidgetBase *widget, int x, int y)
{
    addReportWidget(widget, x, y, true);
}

/*!
  *Adds a new report widget into report. After calling this
  *nethod mouse pointer form line an empty rectangle and
  *will be ready to user click. New widget will be placed
  *in point of mouse click. All widgets that inherits by
  *RReportWidgetBase can be put in report
 * \param widget The widget to insert. All widgets that are
 * \param x The x value of position that widget must be placed
 * \param y The y value of position that widget must be placed
 */
void QReportDocumentDesigner::addReportWidget(QReportWidgetBase *widget, int x, int y, bool addToReport)
{
    Q_D(QReportDocumentDesigner);
    widget->setParentItem(d->pages[0]);

    if (addToReport) {
        widget->setPos(d->report->marginLeft() + x , d->report->marginTop() + y);

        //if (widget->type() == QtReport::widget)
        d->report->widgets()->append(widget);

        if (d->activeBand)
            d->report->changeParent(widget, d->activeBand);

        d->activeWidget = widget;

        emit activeWidgetChanged();
    }//if

    d->report->widgetToFront(widget);

    refreshWidgetParents(widget);

    connect(widget, SIGNAL(moved(QPointF)),
            this,   SLOT(reportWidget_moved(QPointF)));

    connect(widget, SIGNAL(moving(QReportMoveEvent*)),
            this,   SLOT(reportWidget_moving(QReportMoveEvent*)));

    connect(widget, SIGNAL(selectedChanged()),
            this,   SLOT(reportWidget_selectedChanged()));

    connect(widget, SIGNAL(resizing(QReportResizeEvent*)),
            this,   SLOT(reportWidget_resizing(QReportResizeEvent*)));

    connect(widget, SIGNAL(contextMenu()),
            this,   SLOT(reportWidget_contextMenu()));

    //emit activeWidgetChanged();
}


void QReportDocumentDesigner::addBand(QReportBand *band)
{
    addBand(band, true);
}
/*!
  Add new band to Report bands list
*/
void QReportDocumentDesigner::addBand(QReportBand *band, bool addToReport)
{
    Q_D(QReportDocumentDesigner);
//    band->setPos(d->report->marginLeft(), d->report->marginTop());
//    band->setWidth(d->designArea.width() - 1);

    band->setParentItem(d->pages[ 0 ]);

    connect(band, SIGNAL(selectedChanged()),
            this,   SLOT(reportWidget_selectedChanged()));

    connect(band, SIGNAL(resizing(QReportResizeEvent*)),
            this,   SLOT(reportWidget_resizing(QReportResizeEvent*)));

    connect(band, SIGNAL(contextMenu()),
            this,   SLOT(reportWidget_contextMenu()));


    d->activeBand = band;
    d->report->bandToFront(d->activeBand);

    if (addToReport) {
        band->setObjectName(getFreeSectionName(band->header()));
        d->report->bands()->append(band);

        //QReportUndoCommand
    }//if

    reorderBands(true);
    d->resizer->setActiveItem(band);
    d->activeWidget = band;

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(QString(tr("Create %1").arg(band->objectName())));
    cmd->setNewState(getSelectedBandsXML());
    d->undoStack->push(cmd);
    cmd->setReady();
}

/**
 * @brief QReportDocumentDesigner::addDataConnection
 *  Show a QReportDatabaseInfoDialog and request database information from user, If user accept
 *  dialog a connection will be added to the report
 * @return QReportDataConnection that created, If dialog was rejected returns 0
 */
QReportDataConnection *QReportDocumentDesigner::addDataConnection()
{
    Q_D(QReportDocumentDesigner);
    QReportDatabaseInfoDialog info(d->report);

    if(info.exec() != QDialog::Accepted)
        return 0;

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(tr("Create connection"));
    cmd->setOldState(d->report->getXmlContent(QReport::Connection));

    QReportDataConnection *conn = info.dataConnection();
    d->report->addConnection(conn);

    cmd->setNewState(d->report->getXmlContent(QReport::Connection));
    d->undoStack->push(cmd);
    cmd->setReady();

    return conn;
}

/**
 * @brief QReportDocumentDesigner::addDataConnection
 *  Show a QReportDatabaseInfoDialog and request database information from user, If user accept
 *  dialog the connection will be modified
 * @return QReportDataConnection that edited, If dialog was rejected returns 0
 */
QReportDataConnection *QReportDocumentDesigner::editDataConnection(QString connectionName)
{    
    Q_D(QReportDocumentDesigner);
    QReportDataConnection *conn = d->report->connection(connectionName);
    QString oldConnectionName = conn->objectName();

    if(!conn)
        return 0;
    QReportDatabaseInfoDialog info(d->report, conn);

    info.setDataConnection(conn);

    if(info.exec() == QDialog::Accepted){

        QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
        QReportDataConnection *dc = info.dataConnection();
        cmd->setText(tr("Edit connection"));
        cmd->setOldState(d->report->getXmlContent(QReport::Connection));


        conn->setObjectName  (dc->objectName());
        conn->setDriver      (dc->driver());
        conn->setDatabaseName(dc->databaseName());
        conn->setServerName  (dc->serverName());
        conn->setUsername    (dc->username());
        conn->setPassword    (dc->password());

        if(dc->objectName() != oldConnectionName)
            foreach (QReportDataTable *table, d->report->dataTables())
                if(table->connectionName() == oldConnectionName)
                    table->setConnectionName(dc->objectName());

        cmd->setNewState(d->report->getXmlContent(QReport::Connection));
        d->undoStack->push(cmd);
        cmd->setReady();
    }

    return conn;
}

/**
 * @brief QReportDocumentDesigner::addDataConnection
 *  Show a QMessageBox and confrim user to delete the connection, If user press
 *  Yes button the connection will be deleted
 * @return true if user confrim and false if user reject QMessageBox
 */
bool QReportDocumentDesigner::removeDataConnection(QString connectionName)
{
    Q_D(QReportDocumentDesigner);

    QMessageBox msg;
    msg.setIcon(QMessageBox::Question);
    msg.setWindowTitle(tr("Delete connection"));
    msg.setText(tr("Are you sure to delete this connection?"));
    msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::No)
        return false;

    QReportDataConnection *conn = d->report->connection(connectionName);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(tr("Delete connection"));
    cmd->setOldState(d->report->getXmlContent(QReport::Connection));

    d->report->removeConnection(conn);

    cmd->setNewState(d->report->getXmlContent(QReport::Connection));
    d->undoStack->push(cmd);
    cmd->setReady();

    return true;
}

QReportDataTable *QReportDocumentDesigner::addDataTable(QString connectionName)
{
    Q_D(QReportDocumentDesigner);

    QReportDataTableDialog dialog(d->report, connectionName, this);

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(tr("Add data table"));
    cmd->setOldState(d->report->getXmlContent(QReport::DataTable));

    if(dialog.exec() == QDialog::Rejected)
        return 0;

    QReportDataTable *table = dialog.createDataTable();
    d->report->addDataTable(table);

    cmd->setNewState(d->report->getXmlContent(QReport::DataTable));
    d->undoStack->push(cmd);
    cmd->setReady();
    return table;
}

QReportDataTable *QReportDocumentDesigner::editDataTable(QString dataTableName)
{
    Q_D(QReportDocumentDesigner);
    QReportDataTable *table = d->report->dataTable(dataTableName);

    QReportDataTableDialog dialog(d->report, table, this);

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(tr("Edit data table"));
    cmd->setOldState(d->report->getXmlContent(QReport::DataTable));

    if(dialog.exec() == QDialog::Rejected)
        return 0;

    QReportDataTable *t = dialog.createDataTable();

//    table->setConnectionName(t->connectionName());
//    table->setObjectName(t->objectName());

//    foreach (QReportDataField *f, t->fields())
//        table->appendField(f);

    cmd->setNewState(d->report->getXmlContent(QReport::DataTable));
    d->undoStack->push(cmd);
    cmd->setReady();
    return t;
}

bool QReportDocumentDesigner::removeDataTable(QString dataTableName)
{
    Q_D(QReportDocumentDesigner);

    QMessageBox msg;
    msg.setIcon(QMessageBox::Question);
    msg.setWindowTitle(tr("Delete data table"));
    msg.setText(tr("Are you sure to delete this data table?"));
    msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::No)
        return false;

    QReportDataTable *table = d->report->dataTable(dataTableName);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(tr("Delete connection"));
    cmd->setOldState(d->report->getXmlContent(QReport::DataTable));

    d->report->removeDataTable(table);

    cmd->setNewState(d->report->getXmlContent(QReport::DataTable));
    d->undoStack->push(cmd);
    cmd->setReady();

    return true;
}

QReportParametere *QReportDocumentDesigner::addParametere()
{
    Q_D(QReportDocumentDesigner);

    QReportParametereDialog *dialog = new QReportParametereDialog(d->report);
    if(dialog->exec() == QDialog::Rejected)
        return 0;

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(QString(tr("Add parametere %1")).arg(dialog->parametere()->objectName()));
    cmd->setOldState(d->report->getXmlContent(QReport::Parametere));

    d->report->addParametere(dialog->parametere());

    cmd->setNewState(d->report->getXmlContent(QReport::Parametere));
    d->undoStack->push(cmd);
    cmd->setReady();

    return dialog->parametere();
}

QReportParametere *QReportDocumentDesigner::editParametere(QString parametereaName)
{
    Q_D(QReportDocumentDesigner);

    QReportParametere *p = d->report->parameter(parametereaName);
    QReportParametereDialog *dialog = new QReportParametereDialog(d->report, p);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(QString(tr("Edit parametere %1")).arg(p->objectName()));
    cmd->setOldState(d->report->getXmlContent(QReport::Parametere));

    if (dialog->exec() == QDialog::Accepted) {

        p->setObjectName(dialog->parametere()->objectName());
        p->setDefaultValue(dialog->parametere()->defaultValue());
        p->setType(dialog->parametere()->type());

        cmd->setNewState(d->report->getXmlContent(QReport::Parametere));
        d->undoStack->push(cmd);
        cmd->setReady();

        return d->report->parameter(parametereaName);
    } else {
        return 0;
    }
}

bool QReportDocumentDesigner::removeParametere(QString parametereaName)
{
    Q_D(QReportDocumentDesigner);

    QMessageBox msg;
    msg.setIcon(QMessageBox::Question);
    msg.setWindowTitle(tr("Delete parametere"));
    msg.setText(tr("Are you sure to delete this parametere?"));
    msg.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msg.setDefaultButton(QMessageBox::No);

    if(msg.exec() == QMessageBox::No)
        return false;

    QReportParametere *p = d->report->parameter(parametereaName);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText(QString(tr("Delete parametere %1")).arg(p->objectName()));
    cmd->setOldState(d->report->getXmlContent(QReport::Parametere));

    d->report->removeParametere(p);

    cmd->setNewState(d->report->getXmlContent(QReport::Parametere));
    d->undoStack->push(cmd);
    cmd->setReady();
}

void QReportDocumentDesigner::removeReportWidget()
{
    Q_D(QReportDocumentDesigner);
    removeReportWidget(d->activeWidget);
}
void QReportDocumentDesigner::removeReportWidget(QReportWidgetBase *widget)
{
    Q_D(QReportDocumentDesigner);
    /*foreach ( QReportWidgetBase *child, _report->widgets() )
       if( widget == child )
       {
          _report->widgets()->removeOne( child );
          delete child;
          this->repaint();
       }//if
     */

    for (int i = 0; i < d->report->widgets()->count(); i++)
        if (d->report->widgets()->at(i)->objectName() == widget->objectName()) {
            d->report->widgets()->removeAt(i);
            //delete _report->widgets()[i];

            this->repaint();
        }//if

    d->report->removeWidget(widget->objectName());
    d->scene->removeItem(widget);
}

void QReportDocumentDesigner::removeBand(QReportWidgetBase *band)
{
    Q_D(QReportDocumentDesigner);
    d->report->removeBand(band->objectName());
    d->scene->removeItem(band);
}


/**
  * Convert mouse pointer to (+) and initalize scene for psting content of clipboard
  * \see addContent(QString widgetType)
  */
void QReportDocumentDesigner::addContent()
{
    Q_D(QReportDocumentDesigner);

    d->pages[0]->setCursor(Qt::CrossCursor);
    //_readyToPaste = true;
    d->pasteBoard = QApplication::clipboard()->text();
    d->document->setDragMode(QGraphicsView::NoDrag);
    d->pasteDirection = ::Left | ::Top | ::Bottom | ::Right;
    d->pasteMargin.setX(0);
    d->pasteMargin.setY(0);
    d->readyToPaste = true;
    d->pasteInRect = false;
}

/**
  * Convert mouse pointer to (+) and initalize scene for psting new widget. The new widget
  * is a widget that type of \e widgetType. The widget will be created with function
  * QReportWidgetBase::createWidgetFromDom(widgetType).
  * \see addContent()
  */
void QReportDocumentDesigner::addContent(QString widgetType)
{
    Q_D(QReportDocumentDesigner);
    d->pages[0]->setCursor(Qt::CrossCursor);
    //_readyToPaste = true;
    d->pasteBoard = QString("<!DOCTYPE ReportDocument>"
                             "<" COPY_XML_ROOT ">"
                             " <Widget width=\"100\" height=\"50\" type=\"%1\"/>"
                             "</" COPY_XML_ROOT ">").arg(widgetType);
    d->document->setDragMode(QGraphicsView::NoDrag);

    QReportWidgetBase *widget = QReportWidgetBase::createWidget(widgetType);
    d->pasteDirection = widget->resizeDirection();
    d->pasteMargin = widget->marginPos();
    d->readyToPaste = true;
    d->pasteInRect = true;
    delete widget;
}

/**
 * @brief QReportDocumentDesigner::reportWidget
  *Find a widget in remort by it's name
 * @param name The widget's name
 * @return If widget exists return pointer of it, Otherwise return 0.
 */

QReportWidgetBase *QReportDocumentDesigner::reportWidget(QString name)
{
    Q_D(QReportDocumentDesigner);
    QList<QReportWidgetBase*> widgets = *d->report->widgets();
    foreach(QReportWidgetBase *w, widgets)
        if(w->objectName() == name)
            return w;
    return 0;
}

/**
  * @brief QReportDocumentDesigner::applyXml
  *  Apply a xml in document. This funxction remove old element by oldXml
  *  and add new element from newXml
  * @param oldXml    The old xml data
  * @param newXml    The new xml data
  */
void QReportDocumentDesigner::applyXml(QString oldXml, QString newXml)
{
    Q_D(QReportDocumentDesigner);

    QDomDocument oldXmlDoc(XML_ROOT_TAG);
    QDomDocument newXmlDoc(XML_ROOT_TAG);
    oldXmlDoc.setContent(oldXml);
    newXmlDoc.setContent(newXml);
    QDomElement oldWidgetElement = oldXmlDoc.firstChildElement(XML_NODE_REPORT);
    QDomElement newWidgetElement = newXmlDoc.firstChildElement(XML_NODE_REPORT);

    d->applyConnectionsXml(oldWidgetElement, newWidgetElement);
    d->applyWidgetsXml(oldWidgetElement, newWidgetElement);
    d->applyBandsXml(oldWidgetElement, newWidgetElement);
    d->applyParameteresXml(oldWidgetElement, newWidgetElement);
    d->applyDataTablesXml(oldWidgetElement, newWidgetElement);


    if(oldXml.contains(XML_NODE_CONNECTION) || newXml.contains(XML_NODE_CONNECTION)
        || oldXml.contains(XML_NODE_PARAMETER) || newXml.contains(XML_NODE_PARAMETER))
        emit dataDirectoryModified();
}

QReportWidgetBase *QReportDocumentDesigner::createWidgetsFromDom(QDomElement dom)
{
    Q_D(QReportDocumentDesigner);

    QReportWidgetBase *widget = QReportWidgetBase::createWidget(&dom);

    addReportWidget(widget, 0, 0, true);
    widget->loadDom(&dom);
    widget->update();

    refreshWidgetParents(widget);
    d->resizer->addWidget(widget);

    return widget;
}

QList<QReportWidgetBase *> QReportDocumentDesigner::createWidgetsFromXml(QString xml)
{
    QList<QReportWidgetBase *> ret;
    Q_D(QReportDocumentDesigner);
    QDomDocument doc(XML_ROOT_TAG);
    doc.setContent(xml);

    QDomElement elWidget = doc.firstChildElement(COPY_XML_ROOT).firstChildElement("Widget");

    d->resizer->clear();
    for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement("Widget"))
        ret.append(createWidgetsFromDom(elWidget));

    d->resizer->refresh();
    return ret;
}
void QReportDocumentDesigner::removeWidgetsFromXml(QString xml)
{
    Q_D(QReportDocumentDesigner);
    QDomDocument doc(XML_ROOT_TAG);
    doc.setContent(xml);

    QDomElement elWidget = doc.firstChildElement(COPY_XML_ROOT).firstChildElement("Widget");
    for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement("Widget")) {
        QReportWidgetBase *widget = reportWidget(elWidget.attribute("objectName"));
        if(widget) removeReportWidget(widget);
    }

    d->resizer->refresh();
}

/**
 * @brief QReportDocumentDesigner::setMouseTool
 *  Change mouse icon and action (Selector or Grabber)
 * @param mouseTool The mouse tool
 */
void QReportDocumentDesigner::setMouseTool(MouseTool mouseTool)
{
    Q_D(QReportDocumentDesigner);

    switch (mouseTool) {
    case Pointer:
        d->document->setDragMode(QGraphicsView::RubberBandDrag);
        break;

    case Hand:
        d->document->setDragMode(QGraphicsView::ScrollHandDrag);
        break;
    }
}




/**
 * @brief QReportDocumentDesigner::getBandAt
 *  Find and return QSectionBand that contain \e pt point
 * @param pt    The point
 * @return      band if exists in \e pt or 0 if there are no band exists on \e pt
 */
QReportBand *QReportDocumentDesigner::getBandAt(QPointF pt) const
{
    Q_D(const QReportDocumentDesigner);
    for (int i = 0; i < d->report->bands()->count(); i++)
        if (d->report->bands()->at(i)->childRect().contains(pt))
            return d->report->bands()->at(i);
    return 0;
}

QReportBand *QReportDocumentDesigner::getBandAt(qreal h) const
{
    Q_D(const QReportDocumentDesigner);
    for (int i = 0; i < d->report->bands()->count(); i++) {
        QRectF rc = d->report->bands()->at(i)->sceneRect();
        if ((rc.top() < h) && (rc.top() + rc.height() > h))
            return d->report->bands()->at(i);
    }//for
    return 0;

}


void QReportDocumentDesigner::refreshWidgetParents(QReportWidgetBase *widget)
{
    Q_D(QReportDocumentDesigner);
    QReportBand *topBandParent = getBandAt(widget->scenePos().y());
    QReportBand *bottomBandParent = getBandAt(widget->sceneRect().bottom());

    if(topBandParent){
        d->report->changeParent(widget, topBandParent);
        d->activeBand = topBandParent;
        d->report->bandToFront(d->activeBand);

        if(bottomBandParent){
            widget->setSecondParent(bottomBandParent);
            QPointF rcby = bottomBandParent->mapFromScene(widget->sceneRect().bottomRight());
            widget->setTopAtSecondBand(rcby.y());
        }else{
            widget->setSecondParent(0);
        }//if
    } else {
        d->report->changeParent(widget, 0);
    }//if
}


bool QReportDocumentDesigner::hasWidgetClassInfo(QString infoName)
{
    if(!selectedWidgets().count())
        return false;

    bool hasAll = true;
    QList<QReportWidgetBase*>  widgets = selectedWidgets();

    foreach(QReportWidgetBase  *widget, widgets)
        if (!widget->hasClassInfo(infoName))
            hasAll = false;

    return hasAll;
}

QString QReportDocumentDesigner::getSelectedWidgetXML() const
{
    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(XML_NODE_REPORT);
    QDomElement widgets = doc.createElement(XML_NODE_WIDGETS);

    foreach(QReportWidgetBase *widget, selectedWidgets()) {
        QDomElement child = doc.createElement(XML_NODE_WIDGET);

        widget->saveDom(&child);

        widgets.appendChild(child);
    }//foreach

    report.appendChild(widgets);
    doc.appendChild(report);
    return doc.toString();
}

QString QReportDocumentDesigner::getSelectedBandsXML() const
{
    Q_D(const QReportDocumentDesigner);

    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(XML_NODE_REPORT);
    QDomElement bands = doc.createElement(XML_NODE_BANDS);

    QDomElement child = doc.createElement(XML_NODE_BAND);

    if(d->activeBand)
        d->activeBand->saveDom(&child);

    bands.appendChild(child);

    report.appendChild(bands);
    doc.appendChild(report);
    return doc.toString();
}

QString QReportDocumentDesigner::getFreeSectionName(QString perfix) const
{
    Q_D(const QReportDocumentDesigner);
    int i = 0;

    // remove QReport from beginning of class name; e.g. 'QReportRectangle' to 'Rectangle'
    if(perfix.startsWith("QReport"))
        perfix.remove(0, 7);

    while(d->report->section(perfix + QString::number(++i))) {};

    return perfix + QString::number(i);
}

QString QReportDocumentDesigner::getFreeWidgetName(QString perfix) const
{
    Q_D(const QReportDocumentDesigner);
    int i = 0;

    // remove QReport from beginning of class name; e.g. 'QReportRectangle' to 'Rectangle'
    if(perfix.startsWith("QReport"))
        perfix.remove(0, 7);

    while(d->report->findWidgetByName(perfix + QString::number(++i))) {};

    return perfix + QString::number(i);
}

void QReportDocumentDesigner::reorderBands()
{
    reorderBands(false);
}

void QReportDocumentDesigner::reorderBands(bool pos)
{
    Q_D(QReportDocumentDesigner);

    qSort(d->report->bands()->begin(),
          d->report->bands()->end(),
          lessThan);

    int bandTop = d->report->marginTop();
    qreal autoTopValue;

    for (int i = 0; i < d->report->bands()->count(); i++) {
        QReportBand *band = d->report->bands()->at(i);

        autoTopValue = (bandTop + (int)d->report->bands()->at(i)->headerHeight())
                % (int)d->gridSize;

        autoTopValue = d->gridSize - autoTopValue;

        bandTop += autoTopValue;

        if(pos){
            band->setLeft(d->report->marginLeft());
            band->setWidth(d->report->designArea().width());
        }
        band->setTop(bandTop); //this replace all of band's child widgets
        bandTop += d->report->bands()->at(i)->size().height();
        bandTop += 10;
    }//for

    for (int i = 0; i < d->report->widgets()->count(); i++) {
        QReportWidgetBase *widget = d->report->widgets()->at(i);

        if(widget->secondParent()){
            QPointF pt( 0, widget->topAtSecondBand() );
            QRectF rc = widget->sceneRect();

            qreal y = widget->secondParent()->mapToScene(pt).y();

            rc.setHeight( y - rc.top() );

            widget->setHeight(rc.height());
        }

    }
    d->resizer->refresh();
}

void QReportDocumentDesigner::setSceneRect()
{
    Q_D(QReportDocumentDesigner);
    QRectF rcDoc;

    for (int i = 0; i < d->pages.count(); i++) {
        d->pages.at(i)->setPos(0, rcDoc.height());

        rcDoc.setHeight(rcDoc.height() + 20);
        rcDoc = rcDoc.united(d->pages.at(i)->childRect());

        if (i != d->pages.count() - 1)
            rcDoc.setBottom(rcDoc.bottom() + 20);
        else
            rcDoc.setBottom(rcDoc.bottom() + 7);
    }//for
    d->scene->setSceneRect(rcDoc);
}

//-- properties --------------------------------------------------------------------------
/*!
  *Zoom designer's current view.
 * \param zoom Define zoom level. Zoom level must be greater than 25 and
  *less than 400.
 * \see void setZoom(int)
 * \see zoom()
 */
void QReportDocumentDesigner::setZoom(int zoom)
{
    Q_D(QReportDocumentDesigner);
    qreal scale = zoom / 100.00;


    if (25 <= zoom && zoom <= 400) {
        QMatrix matrix;
        matrix.scale(scale, scale);

        d->document->setMatrix(matrix);

        d->resizer->setScale(1 / scale);
        d->hRuler->setPixelPerUnit(96 * scale);
        d->vRuler->setPixelPerUnit(96 * scale);

        d->zoom = zoom;

        updateScrollBars();
        d->resizer->refresh();
    }//if
}

/*!
  *Return designer zoom level
 * \see int zoom()
 * \see zoom
 */
int QReportDocumentDesigner::zoom() const
{
    Q_D(const QReportDocumentDesigner);
    return d->zoom;
}

QUndoStack *QReportDocumentDesigner::undoStack() const
{
    Q_D(const QReportDocumentDesigner);
    return d->undoStack;
}

bool QReportDocumentDesigner::alignToGrid() const
{
    Q_D(const QReportDocumentDesigner);
    return d->alignToGrid;
}

void QReportDocumentDesigner::setAlignToGrid(bool value)
{
    Q_D(QReportDocumentDesigner);
    d->alignToGrid = value;
}



//-- QReportWidgetBase singals -----------------------------------------------------------
void QReportDocumentDesigner::reportWidget_selectedChanged()
{
    Q_D(QReportDocumentDesigner);
    QReportWidgetBase *widget = qobject_cast<QReportWidgetBase*>(sender());

    switch(widget->widgetType()){
    case ::Page:
        d->resizer->setVisible(false);
        d->resizer->clear(true);
        break;
    case ::Widget:
        d->activeWidget = widget;

        if (!d->resizer->isWidgetSelected(widget)) {
            d->scene->clearSelection();
            d->scene->selectedItems().append(widget);
            widget->setSelected(true);
            d->resizer->setActiveItem(widget);
        }//if
        break;
    case ::Band:
        d->activeBand = qobject_cast<QReportBand*>(widget);
        d->lastBandXML = getSelectedBandsXML();

        if (!d->resizer->isWidgetSelected(widget)) {
            d->scene->clearSelection();
            d->scene->selectedItems().append(widget);
            widget->setSelected(true);
            d->resizer->setActiveItem(widget);
        }//if
        break;
    }//switch

    emit activeWidgetChanged();
    //cause bug! widget->ensureVisible();
    d->document->update();

    d->lastXML = getSelectedWidgetXML();
}

void QReportDocumentDesigner::reportWidget_mouseMove(QGraphicsSceneMouseEvent*)
{}
void QReportDocumentDesigner::reportWidget_mousePress(QGraphicsSceneMouseEvent*)
{
    Q_D(QReportDocumentDesigner);
    d->lastXML = getSelectedWidgetXML();
    d->lastBandXML = getSelectedBandsXML();
}
void QReportDocumentDesigner::reportWidget_mouseRelease(QGraphicsSceneMouseEvent*)
{}
void QReportDocumentDesigner::reportWidget_resizing(QReportResizeEvent *event)
{
    Q_D(const QReportDocumentDesigner);
    QReportWidgetBase *senderWidget = dynamic_cast<QReportWidgetBase*>(sender());

    QSizeF newSize = getGridAlignPoint(event->size());

    //senderWidget->setPos( getGridAlignPoint( senderWidget->pos() ) );

    if (senderWidget->widgetType() == ::Band) {
        reorderBands();
//        newSize.setWidth(d->pages[0]->documentArea().width() + 1);
    }//if

    if (newSize.width() < d->gridSize) newSize.setWidth(d->gridSize);
    if (newSize.height() < d->gridSize) newSize.setHeight(d->gridSize);

    /*
    event->ignore();
    QRectF rc = senderWidget->childRect();
    rc = getGridAlignPoint( rc );
    senderWidget->setRect( rc );
  */
}
void QReportDocumentDesigner::reportWidget_resized()
{
    Q_D(QReportDocumentDesigner);

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);

    if(d->resizer->selectedWidgets().count() == 1
        && d->resizer->selectedWidgets().at(0)->widgetType() == ::Band){

        cmd->setText(QString(tr("%1 resized")).arg(d->resizer->selectedWidgets().at(0)->objectName()));
        cmd->setOldState(d->lastBandXML);
        cmd->setNewState(getSelectedBandsXML());

    }else{
        cmd->setText(QString(tr("%1 resized")).arg(d->resizer->selectedWidgets().at(0)->objectName()));
        cmd->setOldState(d->lastXML);
        cmd->setNewState(getSelectedWidgetXML());

        QList<QReportWidgetBase*> widgets = selectedWidgets();
        foreach(QReportWidgetBase *widget, widgets)
            refreshWidgetParents(widget);
    }
    d->undoStack->push(cmd);
    cmd->setReady();
    d->lastXML = getSelectedWidgetXML();
    d->lastBandXML = getSelectedBandsXML();
}
void QReportDocumentDesigner::reportWidget_contextMenu()
{
    emit widgetContextMenuEvent();
}
void QReportDocumentDesigner::reportWidget_moving(QReportMoveEvent *event)
{
    Q_D(QReportDocumentDesigner);
    QPointF pos = getGridAlignPoint(event->point(), d->activeWidget);

    /*
       if( _activeWidget->parentBand() )
          pos.setY( pos.y()
                    - (_gridSize
                         - (int)_activeWidget->parentBand()->headerHeight()
                         % (int)_gridSize
                       ) );

  */
    event->setPoint(pos);

    d->resizer->setVisible(false);
    //resizer->setActiveItem( senderWidget );
}
void QReportDocumentDesigner::reportWidget_moved(QPointF)
{
    Q_D(QReportDocumentDesigner);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);

    cmd->setOldState(d->lastXML);
    cmd->setNewState(getSelectedWidgetXML());
    cmd->setText(QString(tr("%1 moved")).arg(qobject_cast<QReportWidgetBase*>(sender())->objectName()));

    d->undoStack->push(cmd);
    cmd->setReady();
    /*
        do nothing here; ond->_scene_mouseRelease() will cover all of here's code
     */

    d->lastXML = getSelectedWidgetXML();
}

void QReportDocumentDesigner::on_resizer_pointGridNeeded(QReportMoveEvent *event)
{
    event->setPoint(getGridAlignPoint(event->point()));
}
void QReportDocumentDesigner::on_resizer_sizeGridNeeded(QReportResizeEvent *event)
{
    event->setSize(getGridAlignPoint(event->size()));
}

void QReportDocumentDesigner::on_scene_mousePress(QGraphicsSceneMouseEvent *event)
{
    Q_D(QReportDocumentDesigner);
    d->lastXML = getSelectedWidgetXML();

    if(d->readyToPaste){
        d->lastScenePoint = event->lastScenePos();
        d->pasteRect.setTopLeft(event->lastScenePos());
        d->pasteRect.setSize(QSizeF(0, 0));
        d->pasteRectItem->setRect(d->pasteRect);
        d->pasteRectItem->setZValue(9999);
        d->pasteRectItem->setVisible(true);
    }//if
}
void QReportDocumentDesigner::on_scene_mouseMove(QGraphicsSceneMouseEvent *event)
{
    Q_D(QReportDocumentDesigner);
    if(!d->readyToPaste) return;
    if(!d->pasteInRect) return;

    QRectF rc;
    rc.setTopLeft(event->lastScenePos());
    rc.setBottomRight(d->lastScenePoint);

    ::ResizeDirection dir = ~d->pasteDirection;

    if(dir & ::Left || dir & ::Right){
        rc.setLeft(d->lastScenePoint.x());
        rc.setWidth(0);
    }//if
    if(dir & ::Top  || dir & ::Bottom){
        rc.setTop(d->lastScenePoint.y());
        rc.setHeight(0);
    }//if

    d->pasteRect = getGridAlignPoint(rc.normalized());
    d->pasteRectItem->setRect(d->pasteRect);
}
void QReportDocumentDesigner::on_scene_mouseRelease(QGraphicsSceneMouseEvent *event)
{
    Q_D(QReportDocumentDesigner);

    if (!d->readyToPaste) {
        if(d->activeWidget)
            refreshWidgetParents(d->activeWidget);

        d->resizer->refresh();
        event->accept();
        return;
    }

    //release paste status
    d->pages[0]->setCursor(Qt::ArrowCursor);
    d->document->setDragMode(QGraphicsView::RubberBandDrag);
    d->pasteRectItem->setVisible(false);
    d->readyToPaste = false;

    // cancel if rect is null
    //if(!_pasteRect.width() && !_pasteRect.height())
    //    return;

    QDomDocument doc(XML_ROOT_TAG);
    doc.setContent(d->pasteBoard);

    QDomElement elWidget = doc.firstChildElement(COPY_XML_ROOT).firstChildElement("Widget");
    QList<QReportWidgetBase*> widgets;
    QPointF pastePoint(-1, -1);

    //init all widgets from clipboard
    for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement("Widget")) {
        QReportWidgetBase *widget;
        widget = QReportWidgetBase::createWidget(&elWidget);

        widget->loadDom(&elWidget);
        widgets.append(widget);

        if (pastePoint.x() > widget->pos().x() || pastePoint.x() == -1)
            pastePoint.setX(widget->pos().x());

        if (pastePoint.y() > widget->pos().y() || pastePoint.y() == -1)
            pastePoint.setY(widget->pos().y());
    }//for


    d->resizer->clear();
    //create all widgets
    foreach(QReportWidgetBase *widget, widgets) {
        QPointF widgetPos(
                    event->lastScenePos().x() + widget->pos().x() - pastePoint.x(),
                    event->lastScenePos().y() + widget->pos().y() - pastePoint.y());


        widgetPos = getGridAlignPoint(widgetPos, widget);

        //remove margin space and place widget into it
        d->pasteRect.translate(-d->pasteMargin);

        //add widget to report and designer
        addReportWidget(widget, widgetPos.x(), widgetPos.y(), true);

        //is there a drag action or simple click
        if(d->pasteInRect){
            widget->setSize(d->pasteRect.size());
            widget->setPos(d->pasteRect.topLeft());
        } else {
            widget->setPos(widgetPos);
        }

        //find a name for new widget
        widget->setObjectName(getFreeWidgetName(widget->metaObject()->className()));

        //add to resizer and select it as default widget
        d->resizer->addWidget(widget);
        d->activeWidget = widget;

        //find first and second parent
        refreshWidgetParents(widget);
        widget->update();
    }//for

    d->resizer->refresh();

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    if(widgets.count() == 1)
        cmd->setText("Create " + widgets.at(0)->objectName());
    else
        cmd->setText("Create widgets");
    cmd->setNewState(getSelectedWidgetXML());
    d->undoStack->push(cmd);
    cmd->setReady();
}
void QReportDocumentDesigner::on_scene_drop(QGraphicsSceneDragDropEvent *event)
{
    Q_D(QReportDocumentDesigner);

//    QString name = getFreeWidgetName("TextBox_" + event->mimeData()->data("text"));
//    QString text = "{" + event->mimeData()->data("text") + "}";

//    QReportTextBox *textBox = new QReportTextBox();
//    textBox->setObjectName(name);
//    textBox->setText(text);
//    addReportWidget(textBox,
//                    event->scenePos().x() - d->report->marginLeft(),
//                    event->scenePos().y() - d->report->marginTop(),
//                    true);

//    d->resizer->clear();
//    d->resizer->addWidget(textBox);
//    d->resizer->refresh();
//    refreshWidgetParents(textBox);
//    textBox->update();

//    QReportUndoCommand *cmd = new QReportUndoCommand(this);
//    cmd->setReport(d->report);
//    cmd->setOldState("");
//    cmd->setNewState(getSelectedWidgetXML());
//    d->undoStack->push(cmd);
}

void QReportDocumentDesigner::on_scene_selectionChanged()
{
    Q_D(QReportDocumentDesigner);
    d->resizer->clear(false);

    for (int i = 0; i < d->scene->selectedItems().count(); i++) {
        QReportWidgetBase *widget =
                dynamic_cast<QReportWidgetBase*>(d->scene->selectedItems().at(i));

        if (widget)
            if (widget->widgetType() == ::Widget)
                d->resizer->addWidget(widget);

    }

    d->resizer->refreshWidgets();
    d->resizer->setVisible();

    emit activeWidgetChanged();
}

void QReportDocumentDesigner::on_document_scroll(int, int)
{
    updateScrollBars();
}




/*!
  This function return an aligned rect nested to rc
  QReportWidgetBase use this to retrive aligned posotion
  for stepped moving
*/
QRectF QReportDocumentDesigner::getGridAlignPoint(QRectF rc)
{
    QRectF ret = rc;
    ret.setTopLeft(getGridAlignPoint(ret.topLeft()));
    ret.setBottomRight(getGridAlignPoint(ret.bottomRight()));

    return ret;
}

QPointF QReportDocumentDesigner::getGridAlignPoint(const QPointF pt, QReportWidgetBase *widget)
{
    QPointF ret = getGridAlignPoint(pt);

    ret.setX(ret.x() - widget->marginPos().x());
    ret.setY(ret.y() - widget->marginPos().y());

    return ret;
}

/*!
  This function return an aligned point nested to pt
  QReportWidgetBase use this to retrive aligned posotion
  for stepped moving
*/
QPointF QReportDocumentDesigner::getGridAlignPoint(QPointF pt)
{
    Q_D(QReportDocumentDesigner);
    QPointF ret = pt;

    if (d->alignToGrid) {
        //ret.setX( ret.x() + _gridSize / 2 );
        //ret.setY( ret.y() + _gridSize / 2 );

        ret.setX(ret.x() - d->report->marginLeft());
        ret.setY(ret.y() - d->report->marginLeft());

        ret.setX(qRound(ret.x() / d->gridSize)  *d->gridSize);
        ret.setY(qRound(ret.y() / d->gridSize)  *d->gridSize);

        ret.setX(ret.x() + d->report->marginLeft());
        ret.setY(ret.y() + d->report->marginLeft());
    }//if

    return ret;
}

/*!
  This function return an aligned size nested to size
  QReportWidgetBase use this to retrive aligned posotion
  for stepped moving
*/
QSizeF QReportDocumentDesigner::getGridAlignPoint(QSizeF s)
{
    Q_D(QReportDocumentDesigner);
    QSizeF ret = s;

    if (d->alignToGrid) {
        s.setWidth(s.width() + d->gridSize / 2);
        s.setHeight(s.height() + d->gridSize / 2);
        ret.setWidth(qRound(s.width() / d->gridSize)  *d->gridSize);
        ret.setHeight(qRound(s.height() / d->gridSize)  *d->gridSize);
    }//if

    return ret;
}




void QReportDocumentDesigner::resizeEvent(QResizeEvent*)
{
    updateScrollBars();
}

/*!
  This method update and repaint Vertical and Horizontal
  rulers
*/
void QReportDocumentDesigner::updateScrollBars()
{
    Q_D(QReportDocumentDesigner);
    qreal scale = (qreal)d->zoom / 100.00;

    d->hRuler->setRuleWidth(d->report->pageSize().width()  *scale);
    d->vRuler->setRuleWidth(d->report->pageSize().height()  *scale);

    d->hRuler->setStartMargin(d->report->marginLeft()  *scale);
    d->hRuler->setEndMargin(d->report->marginRight()  *scale);
    d->vRuler->setStartMargin(d->report->marginTop()  *scale);
    d->vRuler->setEndMargin(d->report->marginBottom()  *scale);


    QSizeF scrollbarSize(
                d->document->verticalScrollBar()->isVisible()   ? d->document->verticalScrollBar()->width()    + 3 : 0,
                d->document->horizontalScrollBar()->isVisible() ? d->document->horizontalScrollBar()->height() + 3 : 0);

    QSizeF docSize(d->report->pageSize().width()  *scale,
                   d->report->pageSize().height()  *scale);

    if (d->document->width() > docSize.width())
        d->hRuler->setStartPos((d->document->width() - scrollbarSize.width() - docSize.width()) / 2);
    else
        d->hRuler->setStartPos(-d->document->horizontalScrollBar()->value() + 3);

    if (d->document->height() > docSize.height())
        d->vRuler->setStartPos((d->document->height() - scrollbarSize.height() - docSize.height()) / 2);
    else
        d->vRuler->setStartPos(-d->document->verticalScrollBar()->value() + 3);

    d->vRuler->update();
    d->hRuler->update();
}



void QReportDocumentDesigner::setAlign(ResizeDirection direction)
{
    Q_D(QReportDocumentDesigner);

    if (!selectedWidgets().count()) return;

    QRectF rc = selectedWidgets().at(0)->childRect();

    for (int i = 0; i < selectedWidgets().count(); i++)
        rc = rc.united(selectedWidgets().at(i)->childRect());

    for (int i = 0; i < selectedWidgets().count(); i++) {
        QRectF widgetRect = selectedWidgets().at(i)->childRect();
        switch (direction) {
        case ::Top:
            widgetRect.moveTop(rc.top());
            break;

        case ::Left:
            widgetRect.moveLeft(rc.left());
            break;

        case ::Right:
            widgetRect.moveRight(rc.right());
            break;

        case ::Bottom:
            widgetRect.moveBottom(rc.bottom());
            break;
        }//switch
        selectedWidgets()[i]->setChildRect(widgetRect);
    }//for

    d->resizer->refresh();
}


void QReportDocumentDesigner::setReport(QReport *report)
{
    Q_D(QReportDocumentDesigner);
    d->report = report;
}

QReport *QReportDocumentDesigner::report() const
{
    Q_D(const QReportDocumentDesigner);
    return d->report;
}

void QReportDocumentDesigner::setGridType(::GridType type)
{
    Q_D(QReportDocumentDesigner);
    d->pages.at(0)->setGridType(type);
    d->scene->update();
    d->document->update();
}


bool QReportDocumentDesigner::showRulers() const
{
    Q_D(const QReportDocumentDesigner);
    return d->vRuler->isVisible() || d->hRuler->isVisible();
}

void QReportDocumentDesigner::setShowRulers(bool value)
{
    Q_D(QReportDocumentDesigner);
    d->vRuler->setVisible(value);
    d->hRuler->setVisible(value);
}

void QReportDocumentDesigner::createWidget(QString widgetType, QString name, QRectF rc)
{
    Q_D(QReportDocumentDesigner);
    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    QReportWidgetAttributes attributes;

    if(name.isEmpty())
        name = getFreeWidgetName(widgetType);

    attributes.add("left", QString::number(rc.left()));
    attributes.add("top", QString::number(rc.top()));
    attributes.add("width", QString::number(rc.width()));
    attributes.add("height", QString::number(rc.height()));

    QDomElement dom = QReportWidgetBase::createWidgetDom(widgetType, name, attributes);
    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(COPY_XML_ROOT);
    cmd->setOldState(doc.toString());
    report.appendChild(dom);
    cmd->setNewState(doc.toString());
    cmd->setReady();
    d->undoStack->push(cmd);
}

void QReportDocumentDesigner::updateMetrics()
{
    //qApp->desktop()->screen()->physicalDpiX();
}


void QReportDocumentDesigner::showPageSetup()
{
    Q_D(QReportDocumentDesigner);
    qreal marginLeft, marginRight, marginTop, marginBottom;
    QPageSetupDialog *pageSetup;
    pageSetup = new QPageSetupDialog();

    if (pageSetup->exec()) {

        d->report->setSize(pageSetup->printer()->width(),
                            pageSetup->printer()->height());
        pageSetup->printer()->getPageMargins(&marginLeft, &marginTop,
                                             &marginRight, &marginBottom,
                                             QPrinter::DevicePixel);

        d->report->setMargins(marginLeft, marginTop, marginRight, marginBottom);

        d->pageOne->setSize(d->report->pageSize());

        updateScrollBars();

        setSceneRect();

        reorderBands(true);

        d->pageOne->setMargins(d->report->marginLeft(), d->report->marginTop(), d->report->marginRight(), d->report->marginBottom());

        d->scene->update();
        d->document->update();
    }//if
}


void QReportDocumentDesigner::loadReport()
{
    Q_D(QReportDocumentDesigner);
    d->pages[0]->childItems().clear();

    for (int i = 0; i < d->report->bands()->count(); i++) {
        addBand(d->report->bands()->at(i), false);

        QList<QReportWidgetBase*> list = *d->report->bands()->at(i)->childs();
        for (int j = 0; j < list.count(); j++) {
            addReportWidget(list.at(j),
                            0, 0, false);

            list.at(j)->update();
        }

        d->report->bands()->at(i)->update();
    }//for

    QList<QReportWidgetBase*> list = *d->report->widgets();
    for (int i = 0; i < d->report->widgets()->count(); i++) {
        addReportWidget(list.at(i),
                        list.at(i)->pos().x(),
                        list.at(i)->pos().y(),
                        false);

        list.at(i)->update();
    }

    reorderBands();
}

QReportWidgetBase *QReportDocumentDesigner::activeWidget()
{
    Q_D(QReportDocumentDesigner);
    return d->activeWidget;
}

QReportBand *QReportDocumentDesigner::activeBand()
{
    Q_D(QReportDocumentDesigner);
    return d->activeBand;
}





/*!
  Return all selected object in designer
*/
QList<QReportWidgetBase*> QReportDocumentDesigner::selectedWidgets() const
{
    Q_D(const QReportDocumentDesigner);
    QList<QReportWidgetBase*>  ret;

    for (int i = 0; i < d->scene->selectedItems().count(); i++) {
        QReportWidgetBase *widget = (QReportWidgetBase*)d->scene->selectedItems().at(i);
        if (widget->widgetType() == ::Widget)
            ret.append(widget);
    }//for

    return ret;
}

/*!
  Check that the widget has a property
  \param propertyName Thegiven property name for check
*/
bool QReportDocumentDesigner::hasWidgetProperty(QString propertyName)
{
    QList<QReportWidgetBase*>  widgets = selectedWidgets();
    int count = 0;

    foreach(QReportWidgetBase  *widget, widgets)
        if (widget->hasProperty(propertyName))
            count++;

    return count && count == widgets.count();
}

/*!
  Set a value for a property of selected items in designer
  \param propertyName The name of given property
  \param propertyValue The value for property of objects
  \see selectedWidgets()
*/
void QReportDocumentDesigner::setWidgetProperty(QString propertyName, QVariant propertyValue)
{
    QList<QReportWidgetBase*>  widgets = selectedWidgets();

    foreach(QReportWidgetBase  *widget, widgets)
        widget->setPropertyValue(propertyName, propertyValue);

}

/*!
  Return given property value of selected objects. If the value be different from others
  this function will be return QVariant() else return property value.
  \param name Name of property
  \see selectedWidgets()
*/
QVariant QReportDocumentDesigner::widgetProperty(QString name) const
{
    QVariant ret;

    QList<QReportWidgetBase*>  widgets = selectedWidgets();

    if (!widgets.count()) return QVariant();

    ret = widgets.at(0)->propertyValue(name);
    foreach(QReportWidgetBase  *widget, widgets)
        if (widget->propertyValue(name) != ret)
            return QVariant();

    return ret;
}

QStringList QReportDocumentDesigner::widgetProperties() const
{
    QHash<QString, int> propertiesCount;
    QList<QReportWidgetBase*>  widgets = selectedWidgets();

    foreach(QReportWidgetBase  *widget, widgets)
        for (int i = 0; i < widget->metaObject()->propertyCount(); i++)
            propertiesCount[widget->metaObject()->property(i).name()]++;

    QList<QString> keys = propertiesCount.keys();

    QStringList ret;
    foreach(QString key, keys)
        if (propertiesCount[key] == widgets.count())
            ret.append(key);

    return ret;
}




//-- design methods ----------------------------------------------------------------------
QAction *QReportDocumentDesigner::createRedoAction(QObject *parent) const
{
    Q_D(const QReportDocumentDesigner);
    return d->undoStack->createRedoAction(parent);
}
QAction *QReportDocumentDesigner::createUndoAction(QObject *parent) const
{
    Q_D(const QReportDocumentDesigner);
    return d->undoStack->createUndoAction(parent);
}

void QReportDocumentDesigner::clear()
{
    Q_D(QReportDocumentDesigner);

    QReportUndoCommand *cmd = new QReportUndoCommand();
    cmd->setNewState("");
    cmd->setOldState(d->report->getXmlContent());
    cmd->setReady();
    cmd->setDesigner(this);
    cmd->setReport(d->report);
    cmd->redo();

    undoStack()->clear();
}
void QReportDocumentDesigner::setSameSize()
{
    Q_D(QReportDocumentDesigner);
    if (!d->activeWidget) return;

    for (int i = 0; i < selectedWidgets().count(); i++)
        selectedWidgets().at(i)->setSize(d->activeWidget->size());

    d->resizer->refresh();
}
void QReportDocumentDesigner::setSameWidth()
{
    Q_D(QReportDocumentDesigner);
    if (!d->activeWidget) return;

    for (int i = 0; i < selectedWidgets().count(); i++)
        selectedWidgets().at(i)->setWidth(d->activeWidget->width());

    d->resizer->refresh();
}
void QReportDocumentDesigner::setSameHeight()
{
    Q_D(QReportDocumentDesigner);
    if (!d->activeWidget) return;

    for (int i = 0; i < selectedWidgets().count(); i++)
        selectedWidgets().at(i)->setHeight(d->activeWidget->height());

    d->resizer->refresh();
}
void QReportDocumentDesigner::alignToGridWidgets()
{
    Q_D(QReportDocumentDesigner);
    QList<QReportWidgetBase*> widgets = selectedWidgets();

    foreach(QReportWidgetBase  *widget, widgets)
        widget->setChildRect(getGridAlignPoint(widget->sceneRect()));

    d->resizer->refresh();
}
void QReportDocumentDesigner::sendToBack()
{
    Q_D(QReportDocumentDesigner);
    d->report->widgetToBack(d->activeWidget);
}
void QReportDocumentDesigner::bringToFront()
{
    Q_D(QReportDocumentDesigner);
    d->report->widgetToFront(d->activeWidget);
}

void QReportDocumentDesigner::doCopy()
{
    QApplication::clipboard()->setText(getSelectedWidgetXML());
}
void QReportDocumentDesigner::doPaste()
{
    addContent();
}
void QReportDocumentDesigner::doCut()
{
    doCopy();
    doDelete();
}
void QReportDocumentDesigner::doDelete()
{
    Q_D(QReportDocumentDesigner);
    /*foreach(QReportWidgetBase  *widget, selectedWidgets()) {
        d->_scene->removeItem(widget);

        delete widget;
    }*/

    QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);
    cmd->setText("Remove widget(s)");
    cmd->setOldState(getSelectedWidgetXML());
    d->undoStack->push(cmd);
}
void QReportDocumentDesigner::selectAll()
{
    Q_D(QReportDocumentDesigner);
    d->resizer->clear();

    for (int i = 0; i < d->report->widgets()->count(); i++) {
        QReportWidgetBase *widget = d->report->widgets()->at(i);
        qDebug() << widget->objectName();
        //widget->setSelected(true);
        //d->_scene->selectedItems().append(widget);
        d->resizer->addWidget(widget);
    }
    d->resizer->refresh();

    emit activeWidgetChanged();
}

/*!
  Update and redraw all selected items in designer
  \see selectedWidgets()
*/
void QReportDocumentDesigner::updateWidgets()
{
    QList<QReportWidgetBase*>  widgets = selectedWidgets();

    foreach(QReportWidgetBase  *widget, widgets)
        widget->update();
}

void QReportDocumentDesigner::showWidgetProperties()
{
    Q_D(QReportDocumentDesigner);
    QReportPropertyDialog *dialog = new QReportPropertyDialog(this);
    QList<QReportPropertyPageBase*> propertyPages;

    if (selectedWidgets().count() == 1)    propertyPages.append(new QReportPropertyPageWidget());
    if (hasWidgetClassInfo("prop_text"))   propertyPages.append(new QReportPropertyPageText());
    if (hasWidgetClassInfo("prop_font"))   propertyPages.append(new QReportPropertyPageFont());
    if (hasWidgetClassInfo("prop_align"))  propertyPages.append(new QReportPropertyPageAlign());
    if (hasWidgetClassInfo("prop_format")) propertyPages.append(new QReportPropertyPageFormat());
    if (hasWidgetClassInfo("prop_rect"))   propertyPages.append(new QReportPropertyPageRectangle());
    if (hasWidgetClassInfo("prop_line"))   propertyPages.append(new QReportPropertyPageLineType());
    if (hasWidgetClassInfo("prop_image"))  propertyPages.append(new QReportPropertyPageImage());

    if(d->resizer->selectedWidgets().count() == 1
            && d->resizer->selectedWidgets().at(0)->inherits("QReportBand")){
        QReportPropertyBand *p = new QReportPropertyBand();
        p->setBand(d->activeBand);
        propertyPages.append(p);
        propertyPages.append(new QReportPropertySort());
        propertyPages.append(new QReportPropertyFilter());
    }

    foreach(QReportPropertyPageBase  *page, propertyPages) {
        page->setDesigner(this);
        page->load();
        dialog->addTab(page);
    }//foreach

    if (dialog->exec() == QDialog::Accepted) {
        QReportUndoCommand *cmd = new QReportUndoCommand(this, d->report);

        cmd->setText(tr("Widget(s) property changed"));
        if(selectedWidgets().count() == 1)
            cmd->setOldName(d->activeWidget->objectName());
        cmd->setOldState(getSelectedWidgetXML());

        foreach(QReportPropertyPageBase  *page, propertyPages){
            page->save();
        }//foreach

        if(selectedWidgets().count() == 1)
            cmd->setNewName(d->activeWidget->objectName());
        cmd->setNewState(getSelectedWidgetXML());

        d->undoStack->push(cmd);
        cmd->setReady();

        updateWidgets();

        d->resizer->refresh();
    }//if
}

void QReportDocumentDesigner::showWidgetProperties(QReportWidgetBase *widget)
{
    QReportPropertyDialog *dialog = new QReportPropertyDialog(widget, this);
    dialog->exec();
    widget->update();
}


LEAF_END_NAMESPACE
