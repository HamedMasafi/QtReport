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

class QDomElement;
class QGraphicsRectItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneDragDropEvent;
class QGridLayout;
class QUndoStack;
class QResizeEvent;

LEAF_BEGIN_NAMESPACE

class LReport;
class LReportDocumentDesignerPrivate;
class LReportDocumentView;
class LReportPage;
class LReportRuler;
class LReportWidgetBase;
class LReportWidgetResizer;
class LReportBand;
class LReportScene;
class LReportResizeEvent;
class LReportMoveEvent;
class LReportDataConnection;
class LReportParametere;
class LReportDataTable;
class Q_DECL_EXPORT LReportDocumentDesigner : public QWidget
{
    Q_OBJECT

    /*!
          define zoom level of current designer window
          \see int zoom()
          \see void setZoom
        */
    Q_PROPERTY(int zoom READ zoom WRITE setZoom)

private:
    LReportDocumentDesignerPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(LReportDocumentDesigner)

    void addReportWidget(LReportWidgetBase *Widget, int x, int y, bool addToReport);
    void addBand(LReportBand*, bool addToReport);

    void reorderBands();
    void reorderBands(bool pos);
    void updateScrollBars();
    void updateMetrics();
    void refreshWidgetParents(LReportWidgetBase*);


public:
    LReportDocumentDesigner(QWidget *parent, LReport *report);
    ~LReportDocumentDesigner();

    void setSceneRect();

    int zoom() const;

    QUndoStack *undoStack() const;

    bool alignToGrid() const;
    void setAlignToGrid(bool value);

    bool showRulers() const;
    void setShowRulers(bool value);

    void createWidget(QString widgetType, QString name, QRectF rc);

    LReportDataConnection *addDataConnection();
    LReportDataConnection *editDataConnection(QString connectionName);
    bool removeDataConnection(QString connectionName);

    LReportDataTable *addDataTable(QString connectionName);
    LReportDataTable *editDataTable(QString dataTableName);
    bool removeDataTable(QString dataTableName);

    LReportParametere *addParametere();
    LReportParametere *editParametere(QString parametereaName);
    bool removeParametere(QString parametereaName);

    void addReportWidget(LReportWidgetBase *Widget);
    void addReportWidget(LReportWidgetBase *Widget, int x, int y);
    void addBand(LReportBand*);

    void removeReportWidget();
    void removeReportWidget(LReportWidgetBase *Widget);
    void removeBand(LReportWidgetBase *band);

    void setAlign(ResizeDirection direction);

    LReportWidgetBase *reportWidget(QString name);
    LReportBand *getBandAt(QPointF pt) const;
    LReportBand *getBandAt(qreal h) const;

    void setReport(LReport*);
    LReport *report() const;

    QRectF getGridAlignPoint(QRectF rc);
    QPointF getGridAlignPoint(const QPointF);
    QPointF getGridAlignPoint(const QPointF, LReportWidgetBase*);
    QSizeF getGridAlignPoint(const QSizeF);

    void showWidgetProperties();
    void showWidgetProperties(LReportWidgetBase*);

    void sendToBack();
    void bringToFront();

    void setGridType(GridType type);

    void reorderBandWidgets(LReportBand*);

    void showPageSetup();

    void loadReport();

    LReportWidgetBase *activeWidget();
    LReportBand*      activeBand();

    QList<LReportWidgetBase*> selectedWidgets() const;
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
    LReportWidgetBase *createWidgetsFromDom(QDomElement dom);
    QList<LReportWidgetBase *> createWidgetsFromXml(QString xml);
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
    void reportWidget_resizing(LReportResizeEvent*);
    void reportWidget_moving(LReportMoveEvent*);
    void reportWidget_moved(QPointF);
    void reportWidget_resized();
    void reportWidget_contextMenu();

    void on_resizer_pointGridNeeded(LReportMoveEvent*);
    void on_resizer_sizeGridNeeded(LReportResizeEvent*);
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

    friend class LReportDesignerFactory;

};

LEAF_END_NAMESPACE

#endif
