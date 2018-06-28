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

#define CIRCLER 6

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QList>
#include <QCursor>
#include <QPoint>
#include <QPointF>
#include <QDebug>

#include "widgetresizer_p.h"
#include "widgets/widgetbase.h"
#include "widgets/band.h"
#include "event.h"

LEAF_BEGIN_NAMESPACE


ResizeHandle::ResizeHandle(qreal x, qreal y, qreal radius, QGraphicsItem *parent) :
    QGraphicsEllipseItem ( x, y, radius, radius, parent ),
    _radius ( radius )
{
    setPen(QPen(Qt::black, 0));
    //this->setFlags( QGraphicsItem::ItemIsMovable );
}

void ResizeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if ( mousePressed )
    {
        QPointF pt (
                    this->pos().x() - _lastPoint.x(),
                    this->pos().y() - _lastPoint.y() );

        emit moving ( this->mapToScene( event->pos() ) );
    }//if
}

void ResizeHandle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED( event );

    _lastPoint = centerPoint();
    mousePressed = true;
}

void ResizeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED( event );
    emit moved();
    mousePressed = false;

}

QPointF ResizeHandle::centerPoint() const
{
    return QPointF ( pos().x() + _radius / 2,
                     pos().y() + _radius / 2 );
}

QPointF ResizeHandle::lastPoint() const
{
    return _lastPoint;
}

ResizeDirection ResizeHandle::resizeDirection() const
{
    return m_resizeDirection;
}

void ResizeHandle::setResizeDirection(ResizeDirection value)
{
    m_resizeDirection = value;
}

void ResizeHandle::setScale(qreal scale)
{
    _radius = scale;
    this->setRect( 0, 0, scale, scale );
}

/*!
  \class RWidgetResizer
  Create a new RReportWidget resize manager. A resize manager show 8 circle on
  widget that user can drag them to resize the widget
*/
WidgetResizer::WidgetResizer(QGraphicsScene *parent) :
    QObject(),
    parentScene(parent),
    //_parent( 0 ),
    m_scale(1)
{
    resizerTL = new ResizeHandle(0, 0, CIRCLER);
    resizerT  = new ResizeHandle(0, 0, CIRCLER);
    resizerTR = new ResizeHandle(0, 0, CIRCLER);
    resizerL  = new ResizeHandle(0, 0, CIRCLER);
    resizerR  = new ResizeHandle(0, 0, CIRCLER);
    resizerBL = new ResizeHandle(0, 0, CIRCLER);
    resizerB  = new ResizeHandle(0, 0, CIRCLER);
    resizerBR = new ResizeHandle(0, 0, CIRCLER);

    /*parent->addItem( resizerTL );
    parent->addItem( resizerT  );
    parent->addItem( resizerTR );
    parent->addItem( resizerL  );
    parent->addItem( resizerR  );
    parent->addItem( resizerBL );
    parent->addItem( resizerB  );
    parent->addItem( resizerBR );*/

    handles.append(resizerTL);
    handles.append(resizerT);
    handles.append(resizerTR);
    handles.append(resizerL);
    handles.append(resizerR);
    handles.append(resizerBL);
    handles.append(resizerB);
    handles.append(resizerBR);

    resizerTL->setPen(QPen(Qt::black));

    setVisible(false);

    resizerTL->setCursor(Qt::SizeFDiagCursor);
    resizerT->setCursor(Qt::SizeVerCursor);
    resizerTR->setCursor(Qt::SizeBDiagCursor);
    resizerL->setCursor(Qt::SizeHorCursor);
    resizerR->setCursor(Qt::SizeHorCursor);
    resizerBL->setCursor(Qt::SizeBDiagCursor);
    resizerB->setCursor(Qt::SizeVerCursor);
    resizerBR->setCursor(Qt::SizeFDiagCursor);

    resizerT->setResizeDirection(Top);
    resizerL->setResizeDirection(Left);
    resizerR->setResizeDirection(Right);
    resizerB->setResizeDirection(Bottom);

    resizerTR->setResizeDirection(Top    | Right);
    resizerTL->setResizeDirection(Top    | Left);
    resizerBR->setResizeDirection(Bottom | Right);
    resizerBL->setResizeDirection(Bottom | Left);

    for (int i = 0; i < handles.count(); i++) {
        /*QRadialGradient gradient( CIRCLER, CIRCLER, 270);
        gradient.setColorAt(0, QColor::fromRgb(128, 128, 255) );
        gradient.setColorAt(1, QColor::fromRgb(255, 255, 255) );
        handles.at( i )->setBrush( QBrush(gradient) );*/

        handles.at(i)->setBrush(QBrush(Qt::white));
        parent->addItem(handles.at(i));

        connect(handles.at(i), SIGNAL(moving(QPointF)),
                this,          SLOT(handleMoving(QPointF)));

        connect(handles.at(i), SIGNAL(moved()),
                this,          SIGNAL(resized()));

    }//for
}


WidgetResizer::~WidgetResizer()
{
}

void WidgetResizer::setVisible()
{
    if (_selectedWidgets.count() == 1) {
        resizerT->setVisible(_selectedWidgets.at(0)->resizeDirection() & Top);
        resizerL->setVisible(_selectedWidgets.at(0)->resizeDirection() & Left);
        resizerR->setVisible(_selectedWidgets.at(0)->resizeDirection() & Right);
        resizerB->setVisible(_selectedWidgets.at(0)->resizeDirection() & Bottom);

        resizerTR->setVisible(resizerT->isVisible() && resizerR->isVisible());
        resizerTL->setVisible(resizerT->isVisible() && resizerL->isVisible());
        resizerBR->setVisible(resizerB->isVisible() && resizerR->isVisible());
        resizerBL->setVisible(resizerB->isVisible() && resizerL->isVisible());
    }
    else
        setVisible(_selectedWidgets.count());

}

void WidgetResizer::setVisible(bool visible)
{
    for (int i = 0; i < handles.count(); i++)
        handles[ i ]->setVisible(visible);
}

void WidgetResizer::setActiveItem(WidgetBase *item)
{
    clear(true);
    _selectedWidgets.clear();
    _selectedWidgets.append(item);
    item->setSelected(true);

    refreshWidgets();

    selectionRect = item->childRect();
    resizeRect = item->childRect();
    setHandlesOnItem(selectionRect);
    setVisible();
}

void WidgetResizer::setHandlesOnItem(QRectF rc)
{
    //if( !_parent ) return;
    if (!_selectedWidgets.count()) return;

    setResezeHandlePos(resizerTL, rc.topLeft());
    setResezeHandlePos(resizerT,  rc.topRight(), rc.topLeft());
    setResezeHandlePos(resizerTR, rc.topRight());

    setResezeHandlePos(resizerL,  rc.topLeft(),  rc.bottomLeft());
    setResezeHandlePos(resizerR,  rc.topRight(), rc.bottomRight());

    setResezeHandlePos(resizerBL, rc.bottomLeft());
    setResezeHandlePos(resizerB,  rc.bottomRight(), rc.bottomLeft());
    setResezeHandlePos(resizerBR, rc.bottomRight());

    for (int i = 0; i < handles.count(); i++)
        handles.at(i)->setZValue(999);
}

void WidgetResizer::setResezeHandlePos(QGraphicsEllipseItem *handle, QPointF pos)
{
    qreal scaleHalf = m_scale  *CIRCLER / 2;
    handle->setPos(_selectedWidgets.at(0)->parentItem()->mapToParent(   //_parent->mapToParent (
                       pos.x() - scaleHalf,
                       pos.y() - scaleHalf));
}

void WidgetResizer::setResezeHandlePos(QGraphicsEllipseItem *handle, QPointF pos1, QPointF pos2)
{
    qreal scaleHalf = m_scale  *CIRCLER / 2;
    handle->setPos(_selectedWidgets.at(0)->parentItem()->mapToParent(   //_parent->mapToParent (
                       (pos2.x() + pos1.x()) / 2 - scaleHalf,
                       (pos2.y() + pos1.y()) / 2 - scaleHalf));
}

void WidgetResizer::handleMoving(QPointF point)
{
    ResizeHandle *s = qobject_cast<ResizeHandle*> (sender());
    QRectF rc = resizeRect;

    MoveEvent e(point, point);
    emit pointGridNeeded(&e);

    if (!e.isAccepted()) return;

    if (s->resizeDirection() & Top) rc.setTop(e.point().y());
    if (s->resizeDirection() & Left) rc.setLeft(e.point().x());
    if (s->resizeDirection() & Right) rc.setRight(e.point().x());
    if (s->resizeDirection() & Bottom) rc.setBottom(e.point().y());

    if(_selectedWidgets.count() == 1){
        if(rc.width() < _selectedWidgets.at(0)->minimumSize().width())
            rc.setWidth(_selectedWidgets.at(0)->minimumSize().width());
        if(rc.height() < _selectedWidgets.at(0)->minimumSize().height())
            rc.setHeight(_selectedWidgets.at(0)->minimumSize().height());
    }

    if (rc.isValid()) {
        setResezeHandlePos(s, e.point());

        resizeRect = rc;
        proccessNewRect(rc);

        setHandlesOnItem(rc);
    }//if
}


qreal WidgetResizer::scale()
{
    return m_scale;
}
void WidgetResizer::setScale(qreal scale)
{
    m_scale = scale;
    for (int i = 0; i < handles.count(); i++)
        handles.at(i)->setScale(CIRCLER  *scale);
}

void WidgetResizer::proccessNewRect(QRectF rc)
{
    /*if( _selectedWidgets.count() == 1 )
    {
       //rc.setTopLeft(
      //       _selectedWidgets.at(0)->parentItem()->mapFromScene( rc.topLeft() ) );

       _selectedWidgets.at(0)->setPos( rc.topLeft() );
       _selectedWidgets.at(0)->setSize( rc.size() );

       return;
    }*/

    foreach(WidgetBase  *widget, _selectedWidgets) {
        QRectF widgetRect = _widgetRects[widget];
        QSizeF sizeby(
            rc.width()  / selectionRect.width(),
            rc.height() / selectionRect.height());

        widgetRect.moveTop(widgetRect.top()  - selectionRect.top());
        widgetRect.moveLeft(widgetRect.left() - selectionRect.left());

        widgetRect.setTop(widgetRect.top()     *sizeby.height());
        widgetRect.setBottom(widgetRect.bottom()  *sizeby.height());
        widgetRect.setLeft(widgetRect.left()    *sizeby.width());
        widgetRect.setRight(widgetRect.right()   *sizeby.width());

        widgetRect.moveTop(widgetRect.top()  + rc.top());
        widgetRect.moveLeft(widgetRect.left() + rc.left());

        widgetRect.moveTopLeft(widget->parentItem()->mapFromScene(widgetRect.topLeft()));

        widget->setPos(widgetRect.topLeft());
        widget->setSize(widgetRect.width(), widgetRect.height());

    }

    //selectionRect = rc;

}

void WidgetResizer::refresh()
{
    refreshWidgets();
    setVisible();
    refreshHandles();
}

void WidgetResizer::refreshHandles()
{
    setVisible();
}


QList<WidgetBase*> WidgetResizer::selectedWidgets()
{
    return _selectedWidgets;
}

void WidgetResizer::clear()
{
    clear(true);
}

void WidgetResizer::clear(bool unselectWidgets)
{
    foreach(WidgetBase  *widget, _selectedWidgets) {
        if (unselectWidgets)
            widget->setSelected(false);

        disconnect(widget, 0, this, 0);
    }//foreach

    _selectedWidgets.clear();
    setVisible(false);
}

void WidgetResizer::addWidget(WidgetBase *widget)
{
    widget->setSelected(true);

    _selectedWidgets.append(widget);
    connect(widget, SIGNAL(moving(MoveEvent*)),
            this,   SLOT(widgetMoving(MoveEvent*)));
}

void WidgetResizer::refreshWidgets()
{
    QRectF rc;

    if (_selectedWidgets.count() == 0) return;

    rc = _selectedWidgets.at(0)->childRect();
    foreach(WidgetBase  *widget, _selectedWidgets) {
        _widgetRects[widget] = widget->childRect();
        QRectF widgetRect(widget->mapToScene(0, 0), widget->size());
        rc = rc.united(widgetRect);
    }

    selectionRect = rc;
    resizeRect = rc;
    setHandlesOnItem(rc);
}

void WidgetResizer::widgetMoving(MoveEvent *event)
{
    WidgetBase *senderWidget = dynamic_cast<WidgetBase*>(sender());
    QPointF step = senderWidget->mapFromScene(event->point());

    if (step.x() == 0 && step.y() == 0) return;

    foreach(WidgetBase  *widget, _selectedWidgets)
    if (widget != senderWidget)
        widget->moveBy(step.x(), step.y());
}


bool WidgetResizer::isWidgetSelected(WidgetBase *widget)
{
    if (!_selectedWidgets.count()) return false;

    foreach(WidgetBase  *w, _selectedWidgets)
    if (widget == w)
        return true;

    return false;
}

QList<WidgetBase *> WidgetResizer::selectedWidgets() const
{
    return _selectedWidgets;
}


LEAF_END_NAMESPACE
