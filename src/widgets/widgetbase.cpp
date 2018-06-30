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

#include <QMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QMetaProperty>
#include <QDebug>
#include <QDomElement>

#include "event.h"
#include "widgetbase.h"
#include "band.h"

#include "textbox.h"
#include "image.h"
#include "horizontalline.h"
#include "verticalline.h"
#include "rectanglebase.h"
#include "event.h"


LEAF_BEGIN_NAMESPACE

class WidgetBasePrivate
{
public:
    WidgetBasePrivate(WidgetBase *parent) :
        q_ptr(parent),
        fixedSize(0, 0),
        minimumSize(5, 5),
        isMovable(true),
        parentBand(nullptr),
        secondParent(nullptr),
        widgetType(WidgetWidget),
        marginPos(0, 0)
    {

    }

    WidgetType      widgetType;
    QSizeF            fixedSize;
    ResizeDirection   resizeDirection;
    QSizeF            size;
    QSizeF            minimumSize;
    bool              isSelected;
    bool              wasMoved;
    bool              isMovable;
    Panel     *parentBand;
    Band      *secondParent;
    QPointF           childPos;
    QPointF           marginPos;
    qreal             topAtSecondBand;
    QPointF           lastPos;

private:
    WidgetBase  *const q_ptr;
    Q_DECLARE_PUBLIC(WidgetBase)

};

/*!
  \class RReportWidgetBase
  Define report widget, All other widget are inherits by this class.
  This class is base of all report object like RTextBox, RRectangle, ...
  *
*/
WidgetBase::WidgetBase(QGraphicsItem *parent) :
    d_ptr(new WidgetBasePrivate(this)),
    SeriazbleObject(),
    QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setSelected(false);
    this->setZValue(99);    
}



WidgetBase::~WidgetBase()
{
}

ResizeDirection WidgetBase::resizeDirection() const
{
    Q_D(const WidgetBase);
    return d->resizeDirection;
}

void WidgetBase::setResizeDirection(ResizeDirection value)
{
    Q_D(WidgetBase);
    d->resizeDirection = value;
}


// Position and size
/*!
  Return rect of current widget, This rect is based on (0, 0, width, hight)
  if you want to get rect of position and size use childRect.
  \see childRect()
*/
QRectF WidgetBase::boundingRect() const
{
    Q_D(const WidgetBase);
    return QRectF(0, 0, d->size.width(), d->size.height());
}



/*!
  Return left part of widget position. left is pos().x()
*/
qreal WidgetBase::left() const
{
    return pos().x();
}

/*!
  Return top part of widget position. top is pos().y()
*/
qreal WidgetBase::top() const
{
    return pos().y();
}

/*!
  Return with of widget. This is same of the size().width()
  \see size(), height(), setSize()
*/
qreal WidgetBase::width() const
{
    Q_D(const WidgetBase);
    return d->size.width();
}
qreal WidgetBase::height() const
{
    Q_D(const WidgetBase);
    return d->size.height();
}


/*!
  Set left for widget. Left point to X cordinate of pos()
  \see setLeft
  \see pos
*/
void WidgetBase::setLeft(qreal value)
{
    setPos(value, pos().y());
}

/*!
  Set top for widget. Left point to Y cordinate of pos()
  \see setTop
  \see pos
*/
void WidgetBase::setTop(qreal value)
{
    setPos(pos().x(), value);
}

/*!
  *Set width for report widget
 * \see void setSize ( QSizeF size )
 */
void WidgetBase::setWidth(int width)
{
    Q_D(WidgetBase);
    setSize(width, d->size.height());
}

/*!
  *Set height for report widget
 * \see void setSize ( QSizeF size )
 */
void WidgetBase::setHeight(int height)
{
    Q_D(WidgetBase);
    setSize(d->size.width(), height);
}

/*!
  *Return size of report widget; Actualy this is size part of
  *boundingRect()
 */
QSizeF WidgetBase::size() const
{
    Q_D(const WidgetBase);
    return d->size;
}

/*!
  *Set size for current widget, This method affect to boundingRect
 */
void WidgetBase::setSize(QSizeF size)
{
    setSize(size.width(), size.height());
}

/*!
 * \see void setSize ( QSizeF size )
 */
void WidgetBase::setSize(int width, int height)
{
    Q_D(WidgetBase);

    QSize newSize(width, height);
    ResizeEvent resizeEvent(
        newSize,
        QSize(d->size.width(), d->size.height()));

    emit resizing(&resizeEvent);

    if (resizeEvent.isAccepted()) {
        d->size = resizeEvent.size();
        if (d->fixedSize.width() != 0)  d->size.setWidth(d->fixedSize.width());
        if (d->fixedSize.height() != 0) d->size.setHeight(d->fixedSize.height());
        prepareGeometryChange();
    }//if
}

/*!
  Set position for widget
  \see pos
*/
void WidgetBase::setPos(const QPointF& p)
{
    //TODO tidy here
    MoveEvent event(p, pos());
    //emit moving( &event );

    if (event.isAccepted()) {
        QGraphicsItem::setPos(event.point());
    }
}

/*!
  Set position for widget
  \see pos
*/
void WidgetBase::setPos(qreal x, qreal y)
{
    //TODO tidy here
    MoveEvent event(QPointF(x, y), pos());
    //emit moving( &event );

    //if ( event.isAccepted() )
    {
        QGraphicsItem::setPos(event.point());
    }
}

QRectF WidgetBase::rect(bool border) const
{
    Q_D(const WidgetBase);

    if (border)
        return QRectF(0, 0, d->size.width(), d->size.height());
    else
        return QRectF(1, 1, d->size.width() - 1, d->size.height() - 1);
}

/*!
  change rect of current reportWidget without signal emit
*/
void WidgetBase::setRect(const QRectF rc)
{
    Q_D(WidgetBase);
    setPos(rc.topLeft());
    d->size = rc.size();
    prepareGeometryChange();
}

/*!
  Return rect of widget based on it's parent
*/
QRectF WidgetBase::childRect() const
{
    return QRectF(pos(), size());
}

/*!
  Set rect(pos and size) of current widget. The pos for QRectF based on
  parent of widget
*/
void WidgetBase::setChildRect(QRectF rc)
{
    setPos(rc.topLeft());
    setSize(rc.width(), rc.height());
}

/*!
  Return a QRectF that define widget position and size. Size in returned rect
  calculated by scene.
*/
QRectF WidgetBase::sceneRect() const
{
    if (this->parentItem())
        return QRectF(scenePos(), size());
    else
        return childRect();
}

/*!
  Return widget position by it's parent.
  \note The parent of a WidgetBase is not QGraphicsItem::parent()
  \see setChildPos(QPointF pos)
*/
QPointF WidgetBase::childPos() const
{
    Q_D(const WidgetBase);
    return d->childPos;
}

/*!
  Set childPos for current widget
  \see childPos()
*/
void WidgetBase::setChildPos(QPointF pos)
{
    Q_D(WidgetBase);
    d->childPos = pos;
}



QPointF WidgetBase::marginPos() const
{
    Q_D(const WidgetBase);
    return d->marginPos;
}

void WidgetBase::setMarginPos(qreal x, qreal y)
{
    Q_D(WidgetBase);
    d->marginPos = QPointF(x, y);
}

void WidgetBase::setMarginPos(QPointF pt)
{
    Q_D(WidgetBase);
    d->marginPos = pt;
}


/*!
  Return minimum size of widget that can be have.
  \see setMinimumSize ( QSizeF size )
  \see setMinimumSize ( int x, int y )
*/
QSizeF WidgetBase::minimumSize() const
{
    Q_D(const WidgetBase);
    return d->minimumSize;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( int x, int y )
*/
void WidgetBase::setMinimumSize(QSizeF size)
{
    Q_D(WidgetBase);
    d->minimumSize = size;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( QSizeF size )
*/
void WidgetBase::setMinimumSize(int x, int y)
{
    Q_D(WidgetBase);
    d->minimumSize = QSizeF(x, y);
}

void WidgetBase::setFixedSize(qreal width, qreal height)
{
    Q_D(WidgetBase);
    d->fixedSize.setWidth(width);
    d->fixedSize.setHeight(height);
}

void WidgetBase::setFixedSize(QSizeF size)
{
    Q_D(WidgetBase);
    d->fixedSize = size;
}




//Properties
bool WidgetBase::hasProperty(QString prop)
{
    const QMetaObject *metaObject = this->metaObject();
    prop = prop.toLower();

    int count = metaObject->propertyCount();
    for (int i = 0; i < count; i++) {
        QMetaProperty property = metaObject->property(i);

        if (property.isUser() && property.name() == prop)
            return true;

    }//for


    return false;
}

void WidgetBase::setPropertyValue(QString propName, QVariant value)
{
    const QMetaObject *metaObject = this->metaObject();
    //propName = propName.toLower();

    do {
        int count = metaObject->propertyCount();
        for (int i = 0; i < count; i++) {
            QMetaProperty property = metaObject->property(i);

            if (property.isUser() && property.name() == propName) {
                property.write(this, value);
                return;
            }

        }//for
    }
    while ((metaObject = metaObject->superClass()) != 0);
}
QVariant WidgetBase::propertyValue(QString propName)
{
    const QMetaObject *metaObject = this->metaObject();
    //propName = propName.toLower();

    do {
        int count = metaObject->propertyCount();
        for (int i = 0; i < count; i++) {
            QMetaProperty property = metaObject->property(i);

            if (property.isUser() && property.name() == propName)
                return property.read(this);


        }//for
    }
    while ((metaObject = metaObject->superClass()) != 0);

    return QVariant();
}


bool WidgetBase::hasClassInfo(QString infoName)
{
    for (int i = 0; i < metaObject()->classInfoCount(); i++)
        if (metaObject()->classInfo(i).name() == infoName)
            return true;//metaObject()->classInfo(i).value() == "true";

    return false;
}


WidgetBase *WidgetBase::createWidget(QString type)
{
    if (type == "TextBox")         return new TextBox();
    if (type == "Image")           return new Image();
    if (type == "HorizontalLine")  return new HorizontalLine();
    if (type == "VerticalLine")    return new VerticalLine();
    if (type == "Rectangle")       return new Rectangle();
    if (type == "LineBase")        return new Rectangle();

    return 0;
}

WidgetBase *WidgetBase::createWidget(QDomElement *dom)
{
    WidgetBase *widget;
    QString type = dom->attribute("type", "");

    if(type.isEmpty())
        return 0;

    if(widget = createWidget(type))
      widget->loadDom(dom);

    return widget;
}

QString WidgetBase::createWidgetDomString(QString type)
{
//    QString s("<Widget width=\"150\" height=\"75\" type=\"%1\" />");
    return createWidgetDom(type).text();
}

QString WidgetBase::createWidgetDomString(QString type, QString name, WidgetAttributes attributes)
{
//    QString s("<Widget width=\"150\" height=\"75\" type=\"%1\" type=\"%2\"");
//    s = s.arg(type).arg(name);

//    for (int i = 0; i < attributes.size(); ++i)
//        s.append(QString(" \"%1\"=\"%2\"")
//                 .arg(attributes[i].first)
//                 .arg(attributes[i].second));

//    s.append(" />");
//    return s;
    return createWidgetDom(type, name, attributes).text();
}

QDomElement WidgetBase::createWidgetDom(QString type)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("width", 150);
    dom.setAttribute("height", 75);
    return dom;
}
QDomElement WidgetBase::createWidgetDom(QString type, QString name, WidgetAttributes attributes)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("objectName", name);
    for (int i = 0; i < attributes.size(); ++i)
        dom.setAttribute(attributes[i].first, attributes[i].second);

    return dom;
}

void WidgetBase::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(WidgetBase);

    if (!d->isMovable) return;

    emit mouseMove(mouseEvent);

    if (mouseEvent->buttons() & Qt::LeftButton) {
        qreal x, y;
        QPointF oldPoint = this->pos();

        x = mouseEvent->buttonDownPos(Qt::LeftButton).x();
        y = mouseEvent->buttonDownPos(Qt::LeftButton).y();

        MoveEvent event(QPointF(
                                   this->pos().x() + mouseEvent->pos().x() -  x,
                                   this->pos().y() + mouseEvent->pos().y() -  y
                               ),
                               oldPoint);

        if (mouseEvent->pos().x() !=  x ||
            mouseEvent->pos().y() !=  y) {
            d->wasMoved = true;
            emit moving(&event);
        }//if

        if (event.isAccepted()) {
            /*this->moveBy(
                  mouseEvent->pos().x() -  x,
                  mouseEvent->pos().y() -  y );*/
            this->setPos(event.point());
        }
    }//if

    //GraphicsItem::mouseMoveEvent( event );
}

void WidgetBase::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(WidgetBase);
    d->lastPos = pos();
    emit selectedChanged();
    emit mousePress(mouseEvent);
}

void WidgetBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(WidgetBase);
    if (d->wasMoved) {
        emit moved(d->lastPos);
        d->wasMoved = false;
    }//if
    emit mouseRelease(mouseEvent);
}

void WidgetBase::contextMenuEvent(QGraphicsSceneContextMenuEvent*)
{
    emit contextMenu();
}

void WidgetBase::setWidgetType(WidgetType type)
{
    Q_D(WidgetBase);
    d->widgetType = type;
}

/*!
  *Send selected widget to back. after this method current
  *widget will be cover by another widgets
 */
void WidgetBase::sendToBack()
{
    this->setZValue(0);
}

/*!
  *Come selected widget to bring of other widgets.
 */
void WidgetBase::bringToFront()
{
    this->setZValue(99);
}

void WidgetBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->pos().x() < 0) event->ignore();
}

/*!
  Determine that can this report widget move by mouse draging or not.
  \see setIsMovable
*/
bool WidgetBase::isMovable() const
{
    Q_D(const WidgetBase);
    return d->isMovable;
}

/*!
  Set that can this report widget move by mouse draging or not. In this case
  user can drah a RReportWidget and move it to another location. Some of widgets
  like RSectionBand, RDocPage set this property to false and otherones set it
  to true.
  \see isMovable
*/
void WidgetBase::setIsMovable(bool isMovable)
{
    Q_D(WidgetBase);
    d->isMovable = isMovable;
}

const WidgetType WidgetBase::widgetType() const
{
    Q_D(const WidgetBase);
    return d->widgetType;
}


/*!
  Return parent band of current widget. Parent band is a widget that form as
  QSectionBand in report designer that can contain some other widgets.
  \see setParentBand(QSectionBand *widget)
*/
Panel *WidgetBase::parentBand() const
{
    Q_D(const WidgetBase);
    return d->parentBand;
}

void WidgetBase::setParentBand(Panel *widget)
{
    Q_D(WidgetBase);
    //this->setParentItem( widget );
    d->parentBand = widget;
}

Band *WidgetBase::secondParent() const
{
    Q_D(const WidgetBase);
    return d->secondParent;
}

void WidgetBase::setSecondParent(Band *widget)
{
    Q_D(WidgetBase);
    d->secondParent = widget;
}

qreal WidgetBase::topAtSecondBand() const
{
    Q_D(const WidgetBase);
    return d->topAtSecondBand;
}

void WidgetBase::setTopAtSecondBand(qreal value)
{
    Q_D(WidgetBase);
    d->topAtSecondBand = value;
}

LEAF_END_NAMESPACE
