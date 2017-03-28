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

class LReportWidgetBasePrivate
{
public:
    LReportWidgetBasePrivate(LReportWidgetBase *parent) :
        q_ptr(parent),
        fixedSize(0, 0),
        minimumSize(5, 5),
        isMovable(true),
        parentBand(0),
        secondParent(0),
        marginPos(0, 0),
        widgetType(Widget)
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
    LReportPanel     *parentBand;
    LReportBand      *secondParent;
    QPointF           childPos;
    QPointF           marginPos;
    qreal             topAtSecondBand;
    QPointF           lastPos;

private:
    LReportWidgetBase  *const q_ptr;
    Q_DECLARE_PUBLIC(LReportWidgetBase)

};

/*!
  \class RReportWidgetBase
  Define report widget, All other widget are inherits by this class.
  This class is base of all report object like RTextBox, RRectangle, ...
  *
*/
LReportWidgetBase::LReportWidgetBase(QGraphicsItem *parent) :
    d_ptr(new LReportWidgetBasePrivate(this)),
    LReportXMLSeriazble(),
    QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setSelected(false);
    this->setZValue(99);    
}



LReportWidgetBase::~LReportWidgetBase()
{
}

ResizeDirection LReportWidgetBase::resizeDirection() const
{
    Q_D(const LReportWidgetBase);
    return d->resizeDirection;
}

void LReportWidgetBase::setResizeDirection(ResizeDirection value)
{
    Q_D(LReportWidgetBase);
    d->resizeDirection = value;
}


// Position and size
/*!
  Return rect of current widget, This rect is based on (0, 0, width, hight)
  if you want to get rect of position and size use childRect.
  \see childRect()
*/
QRectF LReportWidgetBase::boundingRect() const
{
    Q_D(const LReportWidgetBase);
    return QRectF(0, 0, d->size.width(), d->size.height());
}



/*!
  Return left part of widget position. left is pos().x()
*/
qreal LReportWidgetBase::left() const
{
    return pos().x();
}

/*!
  Return top part of widget position. top is pos().y()
*/
qreal LReportWidgetBase::top() const
{
    return pos().y();
}

/*!
  Return with of widget. This is same of the size().width()
  \see size(), height(), setSize()
*/
qreal LReportWidgetBase::width() const
{
    Q_D(const LReportWidgetBase);
    return d->size.width();
}
qreal LReportWidgetBase::height() const
{
    Q_D(const LReportWidgetBase);
    return d->size.height();
}


/*!
  Set left for widget. Left point to X cordinate of pos()
  \see setLeft
  \see pos
*/
void LReportWidgetBase::setLeft(qreal value)
{
    setPos(value, pos().y());
}

/*!
  Set top for widget. Left point to Y cordinate of pos()
  \see setTop
  \see pos
*/
void LReportWidgetBase::setTop(qreal value)
{
    setPos(pos().x(), value);
}

/*!
  *Set width for report widget
 * \see void setSize ( QSizeF size )
 */
void LReportWidgetBase::setWidth(int width)
{
    Q_D(LReportWidgetBase);
    setSize(width, d->size.height());
}

/*!
  *Set height for report widget
 * \see void setSize ( QSizeF size )
 */
void LReportWidgetBase::setHeight(int height)
{
    Q_D(LReportWidgetBase);
    setSize(d->size.width(), height);
}

/*!
  *Return size of report widget; Actualy this is size part of
  *boundingRect()
 */
QSizeF LReportWidgetBase::size() const
{
    Q_D(const LReportWidgetBase);
    return d->size;
}

/*!
  *Set size for current widget, This method affect to boundingRect
 */
void LReportWidgetBase::setSize(QSizeF size)
{
    setSize(size.width(), size.height());
}

/*!
 * \see void setSize ( QSizeF size )
 */
void LReportWidgetBase::setSize(int width, int height)
{
    Q_D(LReportWidgetBase);

    QSize newSize(width, height);
    LReportResizeEvent resizeEvent(
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
void LReportWidgetBase::setPos(const QPointF& p)
{
    //TODO tidy here
    LReportMoveEvent event(p, pos());
    //emit moving( &event );

    if (event.isAccepted()) {
        QGraphicsItem::setPos(event.point());
    }
}

/*!
  Set position for widget
  \see pos
*/
void LReportWidgetBase::setPos(qreal x, qreal y)
{
    //TODO tidy here
    LReportMoveEvent event(QPointF(x, y), pos());
    //emit moving( &event );

    //if ( event.isAccepted() )
    {
        QGraphicsItem::setPos(event.point());
    }
}

QRectF LReportWidgetBase::rect(bool border) const
{
    Q_D(const LReportWidgetBase);

    if (border)
        return QRectF(0, 0, d->size.width(), d->size.height());
    else
        return QRectF(1, 1, d->size.width() - 1, d->size.height() - 1);
}

/*!
  change rect og current reportWidget without signal emit
*/
void LReportWidgetBase::setRect(const QRectF rc)
{
    Q_D(LReportWidgetBase);
    setPos(rc.topLeft());
    d->size = rc.size();
    prepareGeometryChange();
}

/*!
  Return rect of widget based on it's parent
*/
QRectF LReportWidgetBase::childRect() const
{
    return QRectF(pos(), size());
}

/*!
  Set rect(pos and size) of current widget. The pos for QRectF based on
  parent of widget
*/
void LReportWidgetBase::setChildRect(QRectF rc)
{
    setPos(rc.topLeft());
    setSize(rc.width(), rc.height());
}

/*!
  Return a QRectF that define widget position and size. Size in returned rect
  calculated by scene.
*/
QRectF LReportWidgetBase::sceneRect() const
{
    if (this->parentItem())
        return QRectF(scenePos(), size());
    else
        return childRect();
}

/*!
  Return widget position by it's parent.
  \note The parent of a LReportWidgetBase is not QGraphicsItem::parent()
  \see setChildPos(QPointF pos)
*/
QPointF LReportWidgetBase::childPos() const
{
    Q_D(const LReportWidgetBase);
    return d->childPos;
}

/*!
  Set childPos for current widget
  \see childPos()
*/
void LReportWidgetBase::setChildPos(QPointF pos)
{
    Q_D(LReportWidgetBase);
    d->childPos = pos;
}



QPointF LReportWidgetBase::marginPos() const
{
    Q_D(const LReportWidgetBase);
    return d->marginPos;
}

void LReportWidgetBase::setMarginPos(qreal x, qreal y)
{
    Q_D(LReportWidgetBase);
    d->marginPos = QPointF(x, y);
}

void LReportWidgetBase::setMarginPos(QPointF pt)
{
    Q_D(LReportWidgetBase);
    d->marginPos = pt;
}


/*!
  Return minimum size of widget that can be have.
  \see setMinimumSize ( QSizeF size )
  \see setMinimumSize ( int x, int y )
*/
QSizeF LReportWidgetBase::minimumSize() const
{
    Q_D(const LReportWidgetBase);
    return d->minimumSize;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( int x, int y )
*/
void LReportWidgetBase::setMinimumSize(QSizeF size)
{
    Q_D(LReportWidgetBase);
    d->minimumSize = size;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( QSizeF size )
*/
void LReportWidgetBase::setMinimumSize(int x, int y)
{
    Q_D(LReportWidgetBase);
    d->minimumSize = QSizeF(x, y);
}

void LReportWidgetBase::setFixedSize(qreal width, qreal height)
{
    Q_D(LReportWidgetBase);
    d->fixedSize.setWidth(width);
    d->fixedSize.setHeight(height);
}

void LReportWidgetBase::setFixedSize(QSizeF size)
{
    Q_D(LReportWidgetBase);
    d->fixedSize = size;
}




//Properties
bool LReportWidgetBase::hasProperty(QString prop)
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

void LReportWidgetBase::setPropertyValue(QString propName, QVariant value)
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
QVariant LReportWidgetBase::propertyValue(QString propName)
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


bool LReportWidgetBase::hasClassInfo(QString infoName)
{
    for (int i = 0; i < metaObject()->classInfoCount(); i++)
        if (metaObject()->classInfo(i).name() == infoName)
            return true;//metaObject()->classInfo(i).value() == "true";

    return false;
}


LReportWidgetBase *LReportWidgetBase::createWidget(QString type)
{
    if (type == "LReportTextBox")         return new LReportTextBox();
    if (type == "LReportImage")           return new LReportImage();
    if (type == "LReportHorizontalLine")  return new LReportHorizontalLine();
    if (type == "LReportVerticalLine")    return new LReportVerticalLine();
    if (type == "LReportRectangle")       return new LReportRectangle();
    if (type == "LReportLineBase")        return new LReportRectangle();

    return 0;
}

LReportWidgetBase *LReportWidgetBase::createWidget(QDomElement *dom)
{
    LReportWidgetBase *widget;
    QString type = dom->attribute("type", "");

    if(type.isEmpty())
        return 0;

    if(widget = createWidget(type))
      widget->loadDom(dom);

    return widget;
}

QString LReportWidgetBase::createWidgetDomString(QString type)
{
//    QString s("<Widget width=\"150\" height=\"75\" type=\"%1\" />");
    return createWidgetDom(type).text();
}

QString LReportWidgetBase::createWidgetDomString(QString type, QString name, LReportWidgetAttributes attributes)
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

QDomElement LReportWidgetBase::createWidgetDom(QString type)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("width", 150);
    dom.setAttribute("height", 75);
    return dom;
}
QDomElement LReportWidgetBase::createWidgetDom(QString type, QString name, LReportWidgetAttributes attributes)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("objectName", name);
    for (int i = 0; i < attributes.size(); ++i)
        dom.setAttribute(attributes[i].first, attributes[i].second);

    return dom;
}

void LReportWidgetBase::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(LReportWidgetBase);

    if (!d->isMovable) return;

    emit mouseMove(mouseEvent);

    if (mouseEvent->buttons() & Qt::LeftButton) {
        qreal x, y;
        QPointF oldPoint = this->pos();

        x = mouseEvent->buttonDownPos(Qt::LeftButton).x();
        y = mouseEvent->buttonDownPos(Qt::LeftButton).y();

        LReportMoveEvent event(QPointF(
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

void LReportWidgetBase::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(LReportWidgetBase);
    d->lastPos = pos();
    emit selectedChanged();
    emit mousePress(mouseEvent);
}

void LReportWidgetBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(LReportWidgetBase);
    if (d->wasMoved) {
        emit moved(d->lastPos);
        d->wasMoved = false;
    }//if
    emit mouseRelease(mouseEvent);
}

void LReportWidgetBase::contextMenuEvent(QGraphicsSceneContextMenuEvent*)
{
    emit contextMenu();
}

void LReportWidgetBase::setWidgetType(WidgetType type)
{
    Q_D(LReportWidgetBase);
    d->widgetType = type;
}

/*!
  *Send selected widget to back. after this method current
  *widget will be cover by another widgets
 */
void LReportWidgetBase::sendToBack()
{
    this->setZValue(0);
}

/*!
  *Come selected widget to bring of other widgets.
 */
void LReportWidgetBase::bringToFront()
{
    this->setZValue(99);
}

void LReportWidgetBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->pos().x() < 0) event->ignore();
}

/*!
  Determine that can this report widget move by mouse draging or not.
  \see setIsMovable
*/
bool LReportWidgetBase::isMovable() const
{
    Q_D(const LReportWidgetBase);
    return d->isMovable;
}

/*!
  Set that can this report widget move by mouse draging or not. In this case
  user can drah a RReportWidget and move it to another location. Some of widgets
  like RSectionBand, RDocPage set this property to false and otherones set it
  to true.
  \see isMovable
*/
void LReportWidgetBase::setIsMovable(bool isMovable)
{
    Q_D(LReportWidgetBase);
    d->isMovable = isMovable;
}

const WidgetType LReportWidgetBase::widgetType() const
{
    Q_D(const LReportWidgetBase);
    return d->widgetType;
}


/*!
  Return parent band of current widget. Parent band is a widget that form as
  QSectionBand in report designer that can contain some other widgets.
  \see setParentBand(QSectionBand *widget)
*/
LReportPanel *LReportWidgetBase::parentBand() const
{
    Q_D(const LReportWidgetBase);
    return d->parentBand;
}

void LReportWidgetBase::setParentBand(LReportPanel *widget)
{
    Q_D(LReportWidgetBase);
    //this->setParentItem( widget );
    d->parentBand = widget;
}

LReportBand *LReportWidgetBase::secondParent() const
{
    Q_D(const LReportWidgetBase);
    return d->secondParent;
}

void LReportWidgetBase::setSecondParent(LReportBand *widget)
{
    Q_D(LReportWidgetBase);
    d->secondParent = widget;
}

qreal LReportWidgetBase::topAtSecondBand() const
{
    Q_D(const LReportWidgetBase);
    return d->topAtSecondBand;
}

void LReportWidgetBase::setTopAtSecondBand(qreal value)
{
    Q_D(LReportWidgetBase);
    d->topAtSecondBand = value;
}

LEAF_END_NAMESPACE
