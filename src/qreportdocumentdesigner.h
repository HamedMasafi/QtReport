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

#ifndef RDOCUMENTDESIGNER_H
#define RDOCUMENTDESIGNER_H

#include <QWidget>

#include "qtreportglobal.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QDomElement;
class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneDragDropEvent;
class QGridLayout;
template <typename T> class QList;
class QReport;
class QReportDocumentDesignerPrivate;
class QReportDocumentView;
class QReportPage;
class QReportRuler;
class QReportWidgetBase;
class QReportWidgetResizer;
class QReportBand;
class QReportScene;
class QReportResizeEvent;
class QReportMoveEvent;
class QResizeEvent;
class QUndoStack;
class QReportDataConnection;
class QReportParametere;
class QReportDataTable;
class Q_DECL_EXPORT QReportDocumentDesigner : public QWidget
{
    Q_OBJECT

    /*!
          define zoom level of current designer window
          \see int zoom()
          \see void setZoom
        */
    Q_PROPERTY(int zoom READ zoom WRITE setZoom)

private:
    QReportDocumentDesignerPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(QReportDocumentDesigner)

    void addReportWidget(QReportWidgetBase *Widget, int x, int y, bool addToReport);
    void addBand(QReportBand*, bool addToReport);

    void reorderBands();
    void reorderBands(bool pos);
    void updateScrollBars();
    void updateMetrics();
    void refreshWidgetParents(QReportWidgetBase*);


public:
    QReportDocumentDesigner(QWidget *parent, QReport *report);
    ~QReportDocumentDesigner();

    void setSceneRect();

    int zoom() const;

    QUndoStack *undoStack() const;

    bool alignToGrid() const;
    void setAlignToGrid(bool value);

    bool showRulers() const;
    void setShowRulers(bool value);

    void createWidget(QString widgetType, QString name, QRectF rc);

    QReportDataConnection *addDataConnection();
    QReportDataConnection *editDataConnection(QString connectionName);
    bool removeDataConnection(QString connectionName);

    QReportDataTable *addDataTable(QString connectionName);
    QReportDataTable *editDataTable(QString dataTableName);
    bool removeDataTable(QString dataTableName);

    QReportParametere *addParametere();
    QReportParametere *editParametere(QString parametereaName);
    bool removeParametere(QString parametereaName);

    void addReportWidget(QReportWidgetBase *Widget);
    void addReportWidget(QReportWidgetBase *Widget, int x, int y);
    void addBand(QReportBand*);

    void removeReportWidget();
    void removeReportWidget(QReportWidgetBase *Widget);
    void removeBand(QReportWidgetBase *band);

    void setAlign(ResizeDirection direction);

    QReportWidgetBase *reportWidget(QString name);
    QReportBand *getBandAt(QPointF pt) const;
    QReportBand *getBandAt(qreal h) const;

    void setReport(QReport*);
    QReport *report() const;

    QRectF getGridAlignPoint(QRectF rc);
    QPointF getGridAlignPoint(const QPointF);
    QPointF getGridAlignPoint(const QPointF, QReportWidgetBase*);
    QSizeF getGridAlignPoint(const QSizeF);

    void showWidgetProperties();
    void showWidgetProperties(QReportWidgetBase*);

    void sendToBack();
    void bringToFront();

    void setGridType(::GridType type);

    void reorderBandWidgets(QReportBand*);

    void showPageSetup();

    void loadReport();

    QReportWidgetBase *activeWidget();
    QReportBand*      activeBand();

    QList<QReportWidgetBase*> selectedWidgets() const;
    bool hasWidgetProperty(QString propertyName);
    void setWidgetProperty(QString propertyName, QVariant propertyValue);
    QStringList widgetProperties() const;
    QVariant widgetProperty(QString name) const;
    void updateWidgets();
    bool hasWidgetClassInfo(QString infoName);

    QString getSelectedWidgetXML() const;
    QString getSelectedBandsXML() const;
    QString getFreeSectionName(QString perfix) const;
    QString getFreeWidgetName(QString perfix) const;

    QAction *createRedoAction(QObject *parent) const;
    QAction *createUndoAction(QObject *parent) const;

    void applyXml(QString oldXml, QString newXml);
    QReportWidgetBase *createWidgetsFromDom(QDomElement dom);
    QList<QReportWidgetBase *> createWidgetsFromXml(QString xml);
    void removeWidgetsFromXml(QString xml);

    void setMouseTool(MouseTool mouseTool);

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void on_scene_mouseRelease(QGraphicsSceneMouseEvent *mouseEvent);
    void on_scene_mouseMove(QGraphicsSceneMouseEvent *event);
    void on_scene_mousePress(QGraphicsSceneMouseEvent *event);
    void on_scene_selectionChanged();
    void on_scene_drop(QGraphicsSceneDragDropEvent *event);

    void reportWidget_selectedChanged();
    void reportWidget_mouseMove(QGraphicsSceneMouseEvent *event);
    void reportWidget_mousePress(QGraphicsSceneMouseEvent *event);
    void reportWidget_mouseRelease(QGraphicsSceneMouseEvent *event);
    void reportWidget_resizing(QReportResizeEvent*);
    void reportWidget_moving(QReportMoveEvent*);
    void reportWidget_moved(QPointF);
    void reportWidget_resized();
    void reportWidget_contextMenu();

    void on_resizer_pointGridNeeded(QReportMoveEvent*);
    void on_resizer_sizeGridNeeded(QReportResizeEvent*);
    void on_document_scroll(int, int);

public slots:
    void doCopy();
    void doPaste();
    void doCut();
    void doDelete();
    void selectAll();

    void addContent();
    void addContent(QString widgetType);

    void alignToGridWidgets();
    void setSameSize();
    void setSameWidth();
    void setSameHeight();

    void clear();

    void setZoom(int zoom);

signals:
    void activeWidgetChanged();
    void dataDirectoryModified();
    void widgetContextMenuEvent();

    friend class QReportDesignerFactory;

};

QT_END_NAMESPACE

QT_END_HEADER

#endif
