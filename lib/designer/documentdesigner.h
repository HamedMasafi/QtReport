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

class Report;
class DocumentDesignerPrivate;
class Page;
class Ruler;
class WidgetBase;
class WidgetResizer;
class Band;
class Scene;
class ResizeEvent;
class MoveEvent;
class DataConnection;
class Parametere;
class DataTable;
class Q_DECL_EXPORT DocumentDesigner : public QWidget
{
    Q_OBJECT

    /*!
          define zoom level of current designer window
          \see int zoom()
          \see void setZoom
        */
    Q_PROPERTY(int zoom READ zoom WRITE setZoom)

private:
    DocumentDesignerPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(DocumentDesigner)

    void addReportWidget(WidgetBase *Widget, int x, int y, bool addToReport);
    void addBand(Band*, bool addToReport);

    void reorderBands();
    void reorderBands(bool pos);
    void updateScrollBars();
    void updateMetrics();
    void refreshWidgetParents(WidgetBase*);


public:
    DocumentDesigner(QWidget *parent, Report *report);
    ~DocumentDesigner();

    void setSceneRect();

    int zoom() const;

    QUndoStack *undoStack() const;

    bool alignToGrid() const;
    void setAlignToGrid(bool value);

    bool showRulers() const;
    void setShowRulers(bool value);

    void createWidget(QString widgetType, QString name, QRectF rc);

    DataConnection *addDataConnection();
    DataConnection *editDataConnection(QString connectionName);
    bool removeDataConnection(QString connectionName);

    DataTable *addDataTable(QString connectionName);
    DataTable *editDataTable(QString dataTableName);
    bool removeDataTable(QString dataTableName);

    Parametere *addParametere();
    Parametere *editParametere(QString parametereaName);
    bool removeParametere(QString parametereaName);

    void addReportWidget(WidgetBase *Widget);
    void addReportWidget(WidgetBase *Widget, int x, int y);
    void addBand(Band*);

    void removeReportWidget();
    void removeReportWidget(WidgetBase *Widget);
    void removeBand(WidgetBase *band);

    void setAlign(ResizeDirection direction);

    WidgetBase *reportWidget(QString name);
    Band *getBandAt(QPointF pt) const;
    Band *getBandAt(qreal h) const;

    void setReport(Report*);
    Report *report() const;

    QRectF getGridAlignPoint(QRectF rc);
    QPointF getGridAlignPoint(const QPointF);
    QPointF getGridAlignPoint(const QPointF, WidgetBase*);
    QSizeF getGridAlignPoint(const QSizeF);

    void showWidgetProperties();
    void showWidgetProperties(WidgetBase*);

    void sendToBack();
    void bringToFront();

    void setGridType(GridType type);

    void reorderBandWidgets(Band*);

    void showPageSetup();

    void loadReport();

    WidgetBase *activeWidget();
    Band*      activeBand();

    QList<WidgetBase*> selectedWidgets() const;
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
    WidgetBase *createWidgetsFromDom(QDomElement dom);
    QList<WidgetBase *> createWidgetsFromXml(QString xml);
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
    void reportWidget_resizing(ResizeEvent*);
    void reportWidget_moving(MoveEvent*);
    void reportWidget_moved(QPointF);
    void reportWidget_resized();
    void reportWidget_contextMenu();

    void on_resizer_pointGridNeeded(MoveEvent*);
    void on_resizer_sizeGridNeeded(ResizeEvent*);
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

    friend class DesignerFactory;

};

LEAF_END_NAMESPACE

#endif
