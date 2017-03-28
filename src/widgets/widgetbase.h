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

#ifndef RREPORTWIDGETBASE_H
#define RREPORTWIDGETBASE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QList>
#include <QPair>

#include "qtreportglobal.h"
#include "xmlseriazble.h"

class QGraphicsSceneDragDropEvent;
class QMouseEvent;
class QDomElement;
class QPointF;

LEAF_BEGIN_NAMESPACE

class LReportResizeEvent;
class LReportMoveEvent;
class LReportBand;
class LReportPanel;
class LReportWidgetBasePrivate;
class LReportWidgetAttributes : public QList<QPair<QString, QString> >
{
public:
    LReportWidgetAttributes(){

    }

    void add(QString name, QString value){
        append(qMakePair<QString, QString>(name, value));
    }
};
class LReportWidgetBase : public LReportXMLSeriazble, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_DISABLE_COPY(LReportWidgetBase)

    Q_PROPERTY(qreal left READ left WRITE setLeft USER true)
    Q_PROPERTY(qreal top READ top WRITE setTop USER true)
    Q_PROPERTY(qreal width READ width WRITE setWidth USER true)
    Q_PROPERTY(qreal height READ height WRITE setHeight USER true)
    Q_PROPERTY(QSizeF size WRITE setSize READ size)
    //Q_PROPERTY(LReportPanel *parentBand READ parentBand WRITE setParentBand)
    Q_PROPERTY(QPointF childPos READ childPos WRITE setChildPos)


public:
    LReportWidgetBase(QGraphicsItem *parent = 0);
    ~LReportWidgetBase();


    ResizeDirection resizeDirection() const;
    void setResizeDirection(ResizeDirection value);

    QRectF boundingRect() const;


    void sendToBack();
    void bringToFront();

    int type() {
        return  UserType + 1;
    }

    QSizeF size() const;
    void setSize(QSizeF size);
    void setSize(int x, int y);
    void setWidth(int width);
    void setHeight(int height);


    void setPos(const QPointF& pos);
    void setPos(qreal x, qreal y);
    void setRect(const QRectF rc);

    qreal left() const;
    qreal top() const;
    qreal width() const;
    qreal height() const;

    void setLeft(qreal value);
    void setTop(qreal value);


    QRectF rect(bool border = true) const;
    QRectF childRect() const;
    QRectF sceneRect() const;
    void setChildRect(QRectF rc);

    QSizeF minimumSize() const;
    void setMinimumSize(QSizeF size);
    void setMinimumSize(int x, int y);
    void setFixedSize(qreal width, qreal height);
    void setFixedSize(QSizeF size);

    void comeBackToPos();

    bool isMovable() const;
    void setIsMovable(bool isMovable);

    const WidgetType widgetType() const;

    LReportPanel *parentBand() const;
    void setParentBand(LReportPanel *Widget);

    LReportBand *secondParent() const;
    void setSecondParent(LReportBand *Widget);

    qreal topAtSecondBand() const;
    void setTopAtSecondBand(qreal value);

    QPointF childPos() const;
    void setChildPos(QPointF pos);

    QPointF marginPos() const;
    void setMarginPos(qreal x, qreal y);
    void setMarginPos(QPointF pt);

    void setPropertyValue(QString name, QVariant value);
    bool hasProperty(QString name);
    QVariant propertyValue(QString name);

    static LReportWidgetBase *createWidget(QString type);
    static LReportWidgetBase *createWidget(QDomElement *dom);
    static QString createWidgetDomString(QString type);
    static QString createWidgetDomString(QString type, QString name, LReportWidgetAttributes attributes);
    static QDomElement createWidgetDom(QString type);
    static QDomElement createWidgetDom(QString type, QString name, LReportWidgetAttributes attributes);

    bool hasClassInfo(QString infoName);

protected:
    /*!
          *Render widget on output document.
         * \param painter the document painter pointer.
       */
    void render(QPainter *painter);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setWidgetType(WidgetType type);

private:
    LReportWidgetBasePrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(LReportWidgetBase)

signals:
    void mousePressEvent(QMouseEvent *event);

    void mouseMove(QGraphicsSceneMouseEvent *event);
    void mousePress(QGraphicsSceneMouseEvent *event);
    void mouseRelease(QGraphicsSceneMouseEvent *event);

    void contextMenu();

    void moved(QPointF lastPos);
    void moving(LReportMoveEvent*);
    void resizing(LReportResizeEvent*);

    void selectedChanged();

    friend class LReport;
};

//Q_DECLARE_METATYPE(LReportWidgetBase)

LEAF_END_NAMESPACE

#endif
