/***************************************************************************
 *   QtReport                                                              *
 *   Qt Report Builder Soultion                                            *
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



#include <QList>
#include <QHash>
#include <QVariant>
#include <QSizeF>
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QXmlParseException>
#include <qreportdataconnection.h>

#include "qreportwidgetbase.h"
#include "qreportband.h"
#include "qreport.h"
#include "qreportdatatable.h"
#include "qreportparametere.h"


#define ZMINBAND   10
#define ZMAXBAND   99
#define ZMINWIDGET   100
#define ZMAXWIDGET   999



class QReportPrivate
{
public:
    QReportPrivate(QReport *parent) : q_ptr(parent)
    {

    }

    QList<QReportBand*>           bands;
    QList<QReportWidgetBase*>     widgets;
    QList<QReportDataConnection*> connections;

    qreal marginLeft;
    qreal marginBottom;
    qreal marginTop;
    qreal marginRight;

    QSizeF pageSize;

    QString filePath;

    QList<QReportDataTable*> tables;
    QList<QReportParametere*> parameters;

private :
    QReport  *q_ptr;
    Q_DECLARE_PUBLIC(QReport)
};


/*!
  \classlass QReport
  define a new Report class. Report class can be used for rendering or designing reports
*/
QReport::QReport() : d_ptr(new QReportPrivate(this))
{
}


QList<QReportBand*> *QReport::bands()
{
    Q_D(QReport);
    return &d->bands;
}
QList<QReportWidgetBase*> *QReport::widgets()
{
    Q_D(QReport);
    return &d->widgets;
}

void QReport::removeBand(QString name)
{
    Q_D(QReport);
    name = name.toLower();
    foreach (QReportBand *band, d->bands)
        if(band->objectName().toLower() == name)
            d->bands.removeOne(band);
}

void QReport::removeWidget(QString name)
{
    Q_D(QReport);
    name = name.toLower();
    foreach (QReportWidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == name)
            d->widgets.removeOne(widget);
}



void QReport::setMargins(qreal marginLeft, qreal marginTop,
                         qreal marginRight, qreal marginBottom )
{
    Q_D(QReport);
    d->marginLeft    = marginLeft;
    d->marginBottom  = marginBottom;
    d->marginTop     = marginTop;
    d->marginRight   = marginRight;
}

void QReport::setmarginLeft(qreal value)
{
    Q_D(QReport);
    d->marginLeft = value;
}
void QReport::setMarginRight(qreal value)
{
    Q_D(QReport);
    d->marginRight = value;
}
void QReport::setMarginTop(qreal value)
{
    Q_D(QReport);
    d->marginTop = value;
}
void QReport::setMarginBottom(qreal value)
{
    Q_D(QReport);
    d->marginBottom = value;
}

QSizeF QReport::designArea() const
{
    return QSizeF(pageSize().width() - marginLeft() - marginRight(),
                  pageSize().height() - marginTop() - marginBottom());
}

qreal QReport::marginLeft() const
{
    Q_D(const QReport);
    return d->marginLeft;
}
qreal QReport::marginBottom() const
{
    Q_D(const QReport);
    return d->marginBottom;
}
qreal QReport::marginTop() const
{
    Q_D(const QReport);
    return d->marginTop;
}
qreal QReport::marginRight() const
{
    Q_D(const QReport);
    return d->marginRight;
}

/*!
  ery QReportWidgetBase can be placed on one QSectionBand, This methos change
  rent section of the widget
  aram widget The RReportWidgetBase
  aram parent The new parent of widget
*/
void QReport::changeParent(QReportWidgetBase *widget, QReportBand *parent)
{
    //TODO ...
    if( widget->parentBand() )
        widget->parentBand()->childs()->removeOne( widget );

    if(parent){
        widget->setParentBand( parent );
        widget->setChildPos( parent->mapFromScene( widget->scenePos() ) );
        parent->childs()->append( widget );
    }//if
}

QList<QReportDataTable*> QReport::dataTablesByName(QString tableName)
{
    Q_D(QReport);
    QList<QReportDataTable*> ret;

    foreach(QReportDataTable *datasource, d->tables)
        if(datasource->objectName() == tableName)
            ret.append(datasource);

    return ret;
}


/*!
  turn page size in pixel mode
*/
QSizeF QReport::pageSize() const
{
    Q_D(const QReport);
    return d->pageSize;
}

void QReport::setSize( QSizeF s )
{
    Q_D(QReport);
    d->pageSize = s;
}

void QReport::setSize( qreal width, qreal height )
{
    Q_D(QReport);
    d->pageSize = QSizeF( width, height );
}

void QReport::setWidth( qreal width )
{
    Q_D(QReport);
    d->pageSize = QSizeF( width, d->pageSize.height() );
}

void QReport::setHight( qreal height )
{
    Q_D(QReport);
    d->pageSize = QSizeF( d->pageSize.width(), height );
}

QString QReport::filePath() const
{
    Q_D(const QReport);
    return d->filePath;
}


bool QReport::load( QString path )
{
    Q_D(QReport);

    QFile file( path );

    //QDataStream stream( &file );

    QDomDocument doc("ReportDocument");

    if ( !file.open(QIODevice::ReadWrite) )
        return false;


    QString ems;
    int errorLine = 0;
    int errorColumn = 00;
    if ( !doc.setContent(&file, &ems, &errorLine, &errorColumn) )
    {
        qDebug() << "Error in XML file: "
                 << ems << " Error line:" << errorLine
                 << " Error col:" << errorColumn;
        file.close();
        return false;
    }//if

    QDomElement report = doc.firstChildElement(XML_NODE_REPORT);
    QDomNodeList bands = report.elementsByTagName(XML_NODE_BANDS).at(0).childNodes();
    QDomNodeList connections = report.elementsByTagName(XML_NODE_CONNECTIONS).at(0).childNodes();
    QDomNodeList dataSources = report.elementsByTagName(XML_NODE_DATATABLES).at(0).childNodes();
    QDomNodeList parameteres = report.elementsByTagName(XML_NODE_PARAMETERS).at(0).childNodes();

    //load connections
    if(connections.count() != 0)
        for(int i = 0; i < connections.count(); i++){
            QReportDataConnection *connection = new QReportDataConnection();
            QDomElement el = connections.at(i).toElement();
            connection->loadDom(&el);
            addConnection(connection);
        }

    //load datasources
    if(dataSources.count() != 0)
        for(int i = 0; i < dataSources.count(); i++){
            QDomElement el = dataSources.at(i).toElement();
            QReportDataTable *dataTable = new QReportDataTable(el.attribute("connectionName"));
            dataTable->loadDom(&el);
            addDataTable(dataTable);
        }

    if(parameteres.count() != 0)
        for(int i = 0; i < parameteres.count(); i++){
            QDomElement el = parameteres.at(i).toElement();
            QReportParametere *param = new QReportParametere();
            param->loadDom(&el);
            addParametere(param);
        }

    if(bands.count() != 0)
        for(int i = 0; i < bands.count(); i++){
            QDomElement elBand = bands.at(i).toElement();
            int type = elBand.attribute( "bandType", "0" ).toInt();
            QReportBand *band = new QReportBand( (BandType)type );
            band->loadDom( &elBand );

            QDomElement elWidget = elBand.firstChildElement(XML_NODE_WIDGET);
            for (; !elWidget.isNull(); elWidget = elWidget.nextSiblingElement(XML_NODE_WIDGET)) {
                QReportWidgetBase *widget;
                widget = QReportWidgetBase::createWidget( &elWidget );

                d->widgets.append( widget );
                changeParent( widget, band );

                widget->loadDom( &elWidget );
            }

            d->bands.append(band);
        }//for

    file.close();
    d->filePath = path;
    return true;
}

void QReport::save(QString path)
{
    Q_D(QReport);

    if(path.isEmpty())
        path = d->filePath;

    QFile file(path);
    if(file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly)){
        file.write(getXmlContent());
        file.close();
        d->filePath = path;
    }else{
        //TODO: Show warning message
    }
}

QByteArray QReport::getXmlContent(int NodeFlags) const
{
    Q_D(const QReport);

    QDomDocument doc(XML_ROOT_TAG);
    QDomElement report = doc.createElement(XML_NODE_REPORT);

    if(NodeFlags & Connection){
        QDomElement connectionsDom = doc.createElement(XML_NODE_CONNECTIONS);
        foreach(QReportDataConnection *conn, d->connections){
            QDomElement elConn = doc.createElement(XML_NODE_CONNECTION);
            conn->saveDom(&elConn);
            connectionsDom.appendChild(elConn);
        }//foreach
        report.appendChild( connectionsDom );
    }//if

    if(NodeFlags & Parametere){
        QDomElement parametersDom = doc.createElement(XML_NODE_PARAMETERS);
        foreach(QReportParametere *param, d->parameters){
            QDomElement elParam = doc.createElement(XML_NODE_PARAMETER);
            param->saveDom(&elParam);
            parametersDom.appendChild(elParam);
            report.appendChild( parametersDom );
        }//foreach
    }//if

    if(NodeFlags & DataTable){
        QDomElement dataSourcesDom = doc.createElement(XML_NODE_DATATABLES);
        foreach(QReportDataTable *dataSource, d->tables){
            QDomElement elDataSource = doc.createElement(XML_NODE_DATATABLE);
            dataSource->saveDom(&elDataSource);
            dataSourcesDom.appendChild(elDataSource);
        }//foreach
        report.appendChild( dataSourcesDom );
    }//if


    if(NodeFlags & Band){
        QDomElement bandDom = doc.createElement(XML_NODE_BANDS);
        //save bands
        for( int i = 0; i < d->bands.count(); i++ ) {
            QDomElement band = doc.createElement(XML_NODE_BAND);
            band.setAttribute( "name", d->bands.at(i)->objectName() );
            band.setAttribute( "headerHeight", d->bands.at(i)->headerHeight() );
            band.setAttribute( "bandType", d->bands.at(i)->bandType() );
            d->bands.at(i)->saveDom( &band );

            bandDom.appendChild( band );

            if(NodeFlags & Widget){
                //save current band's widgets
                for( int j = 0; j < d->bands.at(i)->childs()->count(); j++ ) {
                    QDomElement child = doc.createElement(XML_NODE_WIDGET);
                    d->bands.at(i)->childs()->at(j)->saveDom( &child );
                    band.appendChild( child );
                }//for
            }//if
        }//for
        report.appendChild(bandDom);
    }


    //TODO: does not work ***
    if(NodeFlags & Widget){
        QDomElement widgetsDom = doc.createElement(XML_NODE_WIDGETS);

        foreach (QReportWidgetBase *w, d->widgets) {
            if(w->parentBand())
                break;
            QDomElement child = doc.createElement(XML_NODE_WIDGET);
            w->saveDom( &child );
            widgetsDom.appendChild( child );
        }//for

        report.appendChild(widgetsDom);
    }

    doc.appendChild( report );
    return doc.toByteArray();
}

void QReport::widgetToBack( QReportWidgetBase *widget )
{
    Q_D(QReport);
    if( !widget->parentBand() ) return;

    foreach( QReportWidgetBase *child, d->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMAXWIDGET )
            child->setZValue( child->zValue() + 1 );

    widget->setZValue( ZMINWIDGET );
}

void QReport::widgetToFront( QReportWidgetBase *widget )
{
    if( !widget->parentBand() ) return;

    foreach( QReportWidgetBase *child, d_ptr->widgets)// *(widget->parentBand()->childs()) )
        if( child->zValue() != ZMINWIDGET )
            child->setZValue( child->zValue() - 1 );

    widget->setZValue( ZMAXWIDGET );
}

void QReport::bandToBack( QReportBand *band )
{
    Q_D(QReport);
    foreach( QReportBand *section, d->bands )
        if( section->zValue() != ZMAXBAND )
            section->setZValue( section->zValue() + 1 );

    band->setZValue( ZMINBAND );
}

void QReport::bandToFront( QReportBand *band )
{
    Q_D(QReport);
    foreach( QReportBand *section, d->bands )
        if( section->zValue() != ZMINBAND )
            section->setZValue( section->zValue() - 1 );

    band->setZValue( ZMAXBAND );
}

QReportBand *QReport::section(QString sectionName)
{
    Q_D(QReport);
    sectionName = sectionName.toLower();

    foreach(QReportBand *section, d->bands)
        if(section->objectName().toLower() == sectionName)
            return section;

    return 0;
}

QReportWidgetBase *QReport::findWidgetByName(QString widgetName)
{
    Q_D(QReport);
    widgetName = widgetName.toLower();

    foreach(QReportWidgetBase *widget, d->widgets)
        if(widget->objectName().toLower() == widgetName)
            return widget;

    return 0;
}

QReportBand *QReport::findBandByName(QString bandName)
{
    Q_D(QReport);
    bandName = bandName.toLower();

    foreach(QReportBand *band, d->bands)
        if(band->objectName().toLower() == bandName)
            return band;

    return 0;
}

QReportDataConnection *QReport::findConnectionByName(QString connectionName)
{
    Q_D(QReport);
    connectionName = connectionName.toLower();

    foreach(QReportDataConnection *conn, d->connections)
        if(conn->objectName().toLower() == connectionName)
            return conn;

    return 0;
}



QList<QReportDataTable*> QReport::dataTablesByConnections(QString connectionName)
{
    Q_D(QReport);
    QList<QReportDataTable*> ret;

    foreach(QReportDataTable *datatable, d->tables)
        if(datatable->connectionName() == connectionName)
            ret.append(datatable);

    return ret;
}

QList<QReportDataTable*> QReport::dataTables()
{
    Q_D(const QReport);
    return d->tables;
}

void QReport::addDataTable(QReportDataTable *tableName)
{
    Q_D(QReport);
    d->tables.append( tableName );
}

QReportDataTable *QReport::dataTable(QString tableName)
{
    Q_D(QReport);
    tableName = tableName.toLower();

    foreach(QReportDataTable *table, d->tables)
        if(table->objectName().toLower() == tableName)
            return table;

    return 0;
}

QReportDataTable *QReport::dataTable(QString tableName, QString connectionName)
{
    Q_D(QReport);
    tableName = tableName.toLower();
    connectionName = connectionName.toLower();

    foreach(QReportDataTable *table, d->tables)
        if(table->objectName().toLower() == tableName && table->connectionName() == connectionName)
            return table;

    return 0;
}

void QReport::removeDataTable(QReportDataTable *table)
{
    Q_D(QReport);
    d->tables.removeOne(table);
}

QReportParametere *QReport::parameter(QString name)
{
    Q_D(QReport);
    foreach(QReportParametere *param, d->parameters)
        if(param->objectName() == name)
            return param;
    return 0;
}

QList<QReportParametere*> QReport::parameters()
{
    Q_D(const QReport);
    return d->parameters;
}

void QReport::addParametere( QString name, QVariant value )
{
    QReportParametere *param = new QReportParametere( name, value );
    addParametere( param );
}


void QReport::setParameterValue(QString paramName, QVariant value)
{
    parameter(paramName)->setValue(value);
}

void QReport::addParametere( QReportParametere *param )
{
    Q_D(QReport);
    if( !parameter(param->objectName()))
        d->parameters.append( param );
}

void QReport::setParametereValue(QString name, QVariant value)
{
    Q_D(QReport);
    foreach(QReportParametere *param, d->parameters)
        if(param->objectName() == name)
            param->setValue(value);
}

void QReport::removeParametere(QReportParametere *param)
{
    Q_D(QReport);
    d->parameters.removeOne(param);
}

/**
  * Return all connections in current report
  */
QList<QReportDataConnection*> QReport::connections() const
{
    Q_D(const QReport);
    return d->connections;
}

/**
  * Add new connection to report. A connection is an object of \e QReportDataConnection type
  * that can have one or more datasource for data defention. A connection used for report
  * designing, At runtime data from QtSql module replace by this connections.
  */
void QReport::addConnection(QReportDataConnection *conn)
{
    Q_D(QReport);
    if(!connection(conn->objectName()))
        d->connections.append(conn);
}

void QReport::removeConnection(QReportDataConnection *conn)
{
    Q_D(QReport);
    for(int i = 0; i < d->connections.count(); i++)
        if(d->connections.at(i)->objectName() == conn->objectName()){
            d->connections.removeAt(i);
            break;
        }
}

/*!
  Find and return a connection named \e connectionName if there are no connection names
  \e connectionName return 0.
  */
QReportDataConnection *QReport::connection(QString connectionName)
{
    Q_D(QReport);
    foreach(QReportDataConnection *conn, d->connections)
        if(conn->objectName() == connectionName)
            return conn;

    return 0;
}
