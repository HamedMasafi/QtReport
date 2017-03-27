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

#include "qreportevent.h"
#include "qreportwidgetbase.h"
#include "qreportband.h"

#include "qreporttextbox.h"
#include "qreportimage.h"
#include "qreporthorizontalline.h"
#include "qreportverticalline.h"
#include "qreportrectanglebase.h"
#include "qreportevent.h"


LEAF_BEGIN_NAMESPACE

class QReportWidgetBasePrivate
{
public:
    QReportWidgetBasePrivate(QReportWidgetBase *parent) :
        q_ptr(parent),
        fixedSize(0, 0),
        minimumSize(5, 5),
        isMovable(true),
        parentBand(0),
        secondParent(0),
        marginPos(0, 0),
        widgetType(::Widget)
    {

    }

    ::WidgetType      widgetType;
    QSizeF            fixedSize;
    ResizeDirection   resizeDirection;
    QSizeF            size;
    QSizeF            minimumSize;
    bool              isSelected;
    bool              wasMoved;
    bool              isMovable;
    QReportPanel     *parentBand;
    QReportBand      *secondParent;
    QPointF           childPos;
    QPointF           marginPos;
    qreal             topAtSecondBand;
    QPointF           lastPos;

private:
    QReportWidgetBase  *const q_ptr;
    Q_DECLARE_PUBLIC(QReportWidgetBase)

};

/*!
  \class RReportWidgetBase
  Define report widget, All other widget are inherits by this class.
  This class is base of all report object like RTextBox, RRectangle, ...
  *
*/
QReportWidgetBase::QReportWidgetBase(QGraphicsItem *parent) :
    d_ptr(new QReportWidgetBasePrivate(this)),
    QReportXMLSeriazble(),
    QGraphicsItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setSelected(false);
    this->setZValue(99);    
}



QReportWidgetBase::~QReportWidgetBase()
{
}

::ResizeDirection QReportWidgetBase::resizeDirection() const
{
    Q_D(const QReportWidgetBase);
    return d->resizeDirection;
}

void QReportWidgetBase::setResizeDirection(::ResizeDirection value)
{
    Q_D(QReportWidgetBase);
    d->resizeDirection = value;
}


// Position and size
/*!
  Return rect of current widget, This rect is based on (0, 0, width, hight)
  if you want to get rect of position and size use childRect.
  \see childRect()
*/
QRectF QReportWidgetBase::boundingRect() const
{
    Q_D(const QReportWidgetBase);
    return QRectF(0, 0, d->size.width(), d->size.height());
}



/*!
  Return left part of widget position. left is pos().x()
*/
qreal QReportWidgetBase::left() const
{
    return pos().x();
}

/*!
  Return top part of widget position. top is pos().y()
*/
qreal QReportWidgetBase::top() const
{
    return pos().y();
}

/*!
  Return with of widget. This is same of the size().width()
  \see size(), height(), setSize()
*/
qreal QReportWidgetBase::width() const
{
    Q_D(const QReportWidgetBase);
    return d->size.width();
}
qreal QReportWidgetBase::height() const
{
    Q_D(const QReportWidgetBase);
    return d->size.height();
}


/*!
  Set left for widget. Left point to X cordinate of pos()
  \see setLeft
  \see pos
*/
void QReportWidgetBase::setLeft(qreal value)
{
    setPos(value, pos().y());
}

/*!
  Set top for widget. Left point to Y cordinate of pos()
  \see setTop
  \see pos
*/
void QReportWidgetBase::setTop(qreal value)
{
    setPos(pos().x(), value);
}

/*!
  *Set width for report widget
 * \see void setSize ( QSizeF size )
 */
void QReportWidgetBase::setWidth(int width)
{
    Q_D(QReportWidgetBase);
    setSize(width, d->size.height());
}

/*!
  *Set height for report widget
 * \see void setSize ( QSizeF size )
 */
void QReportWidgetBase::setHeight(int height)
{
    Q_D(QReportWidgetBase);
    setSize(d->size.width(), height);
}

/*!
  *Return size of report widget; Actualy this is size part of
  *boundingRect()
 */
QSizeF QReportWidgetBase::size() const
{
    Q_D(const QReportWidgetBase);
    return d->size;
}

/*!
  *Set size for current widget, This method affect to boundingRect
 */
void QReportWidgetBase::setSize(QSizeF size)
{
    setSize(size.width(), size.height());
}

/*!
 * \see void setSize ( QSizeF size )
 */
void QReportWidgetBase::setSize(int width, int height)
{
    Q_D(QReportWidgetBase);

    QSize newSize(width, height);
    QReportResizeEvent resizeEvent(
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
void QReportWidgetBase::setPos(const QPointF& p)
{
    //TODO tidy here
    QReportMoveEvent event(p, pos());
    //emit moving( &event );

    if (event.isAccepted()) {
        QGraphicsItem::setPos(event.point());
    }
}

/*!
  Set position for widget
  \see pos
*/
void QReportWidgetBase::setPos(qreal x, qreal y)
{
    //TODO tidy here
    QReportMoveEvent event(QPointF(x, y), pos());
    //emit moving( &event );

    //if ( event.isAccepted() )
    {
        QGraphicsItem::setPos(event.point());
    }
}

QRectF QReportWidgetBase::rect(bool border) const
{
    Q_D(const QReportWidgetBase);

    if (border)
        return QRectF(0, 0, d->size.width(), d->size.height());
    else
        return QRectF(1, 1, d->size.width() - 1, d->size.height() - 1);
}

/*!
  change rect og current reportWidget without signal emit
*/
void QReportWidgetBase::setRect(const QRectF rc)
{
    Q_D(QReportWidgetBase);
    setPos(rc.topLeft());
    d->size = rc.size();
    prepareGeometryChange();
}

/*!
  Return rect of widget based on it's parent
*/
QRectF QReportWidgetBase::childRect() const
{
    return QRectF(pos(), size());
}

/*!
  Set rect(pos and size) of current widget. The pos for QRectF based on
  parent of widget
*/
void QReportWidgetBase::setChildRect(QRectF rc)
{
    setPos(rc.topLeft());
    setSize(rc.width(), rc.height());
}

/*!
  Return a QRectF that define widget position and size. Size in returned rect
  calculated by scene.
*/
QRectF QReportWidgetBase::sceneRect() const
{
    if (this->parentItem())
        return QRectF(scenePos(), size());
    else
        return childRect();
}

/*!
  Return widget position by it's parent.
  \note The parent of a QReportWidgetBase is not QGraphicsItem::parent()
  \see setChildPos(QPointF pos)
*/
QPointF QReportWidgetBase::childPos() const
{
    Q_D(const QReportWidgetBase);
    return d->childPos;
}

/*!
  Set childPos for current widget
  \see childPos()
*/
void QReportWidgetBase::setChildPos(QPointF pos)
{
    Q_D(QReportWidgetBase);
    d->childPos = pos;
}



QPointF QReportWidgetBase::marginPos() const
{
    Q_D(const QReportWidgetBase);
    return d->marginPos;
}

void QReportWidgetBase::setMarginPos(qreal x, qreal y)
{
    Q_D(QReportWidgetBase);
    d->marginPos = QPointF(x, y);
}

void QReportWidgetBase::setMarginPos(QPointF pt)
{
    Q_D(QReportWidgetBase);
    d->marginPos = pt;
}


/*!
  Return minimum size of widget that can be have.
  \see setMinimumSize ( QSizeF size )
  \see setMinimumSize ( int x, int y )
*/
QSizeF QReportWidgetBase::minimumSize() const
{
    Q_D(const QReportWidgetBase);
    return d->minimumSize;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( int x, int y )
*/
void QReportWidgetBase::setMinimumSize(QSizeF size)
{
    Q_D(QReportWidgetBase);
    d->minimumSize = size;
}

/*!
  Define minimum size of widget
  \see minimumSize()
  \see setMinimumSize ( QSizeF size )
*/
void QReportWidgetBase::setMinimumSize(int x, int y)
{
    Q_D(QReportWidgetBase);
    d->minimumSize = QSizeF(x, y);
}

void QReportWidgetBase::setFixedSize(qreal width, qreal height)
{
    Q_D(QReportWidgetBase);
    d->fixedSize.setWidth(width);
    d->fixedSize.setHeight(height);
}

void QReportWidgetBase::setFixedSize(QSizeF size)
{
    Q_D(QReportWidgetBase);
    d->fixedSize = size;
}




//Properties
bool QReportWidgetBase::hasProperty(QString prop)
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

void QReportWidgetBase::setPropertyValue(QString propName, QVariant value)
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
QVariant QReportWidgetBase::propertyValue(QString propName)
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


bool QReportWidgetBase::hasClassInfo(QString infoName)
{
    for (int i = 0; i < metaObject()->classInfoCount(); i++)
        if (metaObject()->classInfo(i).name() == infoName)
            return true;//metaObject()->classInfo(i).value() == "true";

    return false;
}


QReportWidgetBase *QReportWidgetBase::createWidget(QString type)
{
    if (type == "QReportTextBox")         return new QReportTextBox();
    if (type == "QReportImage")           return new QReportImage();
    if (type == "QReportHorizontalLine")  return new QReportHorizontalLine();
    if (type == "QReportVerticalLine")    return new QReportVerticalLine();
    if (type == "QReportRectangle")       return new QReportRectangle();
    if (type == "QReportLineBase")        return new QReportRectangle();

    return 0;
}

QReportWidgetBase *QReportWidgetBase::createWidget(QDomElement *dom)
{
    QReportWidgetBase *widget;
    QString type = dom->attribute("type", "");

    if(type.isEmpty())
        return 0;

    if(widget = createWidget(type))
      widget->loadDom(dom);

    return widget;
}

QString QReportWidgetBase::createWidgetDomString(QString type)
{
//    QString s("<Widget width=\"150\" height=\"75\" type=\"%1\" />");
    return createWidgetDom(type).text();
}

QString QReportWidgetBase::createWidgetDomString(QString type, QString name, QReportWidgetAttributes attributes)
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

QDomElement QReportWidgetBase::createWidgetDom(QString type)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("width", 150);
    dom.setAttribute("height", 75);
    return dom;
}
QDomElement QReportWidgetBase::createWidgetDom(QString type, QString name, QReportWidgetAttributes attributes)
{
    QDomElement dom;
    dom.setAttribute("type", type);
    dom.setAttribute("objectName", name);
    for (int i = 0; i < attributes.size(); ++i)
        dom.setAttribute(attributes[i].first, attributes[i].second);

    return dom;
}

void QReportWidgetBase::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(QReportWidgetBase);

    if (!d->isMovable) return;

    emit mouseMove(mouseEvent);

    if (mouseEvent->buttons() & Qt::LeftButton) {
        qreal x, y;
        QPointF oldPoint = this->pos();

        x = mouseEvent->buttonDownPos(Qt::LeftButton).x();
        y = mouseEvent->buttonDownPos(Qt::LeftButton).y();

        QReportMoveEvent event(QPointF(
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

void QReportWidgetBase::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(QReportWidgetBase);
    d->lastPos = pos();
    emit selectedChanged();
    emit mousePress(mouseEvent);
}

void QReportWidgetBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_D(QReportWidgetBase);
    if (d->wasMoved) {
        emit moved(d->lastPos);
        d->wasMoved = false;
    }//if
    emit mouseRelease(mouseEvent);
}

void QReportWidgetBase::contextMenuEvent(QGraphicsSceneContextMenuEvent*)
{
    emit contextMenu();
}

void QReportWidgetBase::setWidgetType(WidgetType type)
{
    Q_D(QReportWidgetBase);
    d->widgetType = type;
}

/*!
  *Send selected widget to back. after this method current
  *widget will be cover by another widgets
 */
void QReportWidgetBase::sendToBack()
{
    this->setZValue(0);
}

/*!
  *Come selected widget to bring of other widgets.
 */
void QReportWidgetBase::bringToFront()
{
    this->setZValue(99);
}

void QReportWidgetBase::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->pos().x() < 0) event->ignore();
}

/*!
  Determine that can this report widget move by mouse draging or not.
  \see setIsMovable
*/
bool QReportWidgetBase::isMovable() const
{
    Q_D(const QReportWidgetBase);
    return d->isMovable;
}

/*!
  Set that can this report widget move by mouse draging or not. In this case
  user can drah a RReportWidget and move it to another location. Some of widgets
  like RSectionBand, RDocPage set this property to false and otherones set it
  to true.
  \see isMovable
*/
void QReportWidgetBase::setIsMovable(bool isMovable)
{
    Q_D(QReportWidgetBase);
    d->isMovable = isMovable;
}

const ::WidgetType QReportWidgetBase::widgetType() const
{
    Q_D(const QReportWidgetBase);
    return d->widgetType;
}


/*!
  Return parent band of current widget. Parent band is a widget that form as
  QSectionBand in report designer that can contain some other widgets.
  \see setParentBand(QSectionBand *widget)
*/
QReportPanel *QReportWidgetBase::parentBand() const
{
    Q_D(const QReportWidgetBase);
    return d->parentBand;
}

void QReportWidgetBase::setParentBand(QReportPanel *widget)
{
    Q_D(QReportWidgetBase);
    //this->setParentItem( widget );
    d->parentBand = widget;
}

QReportBand *QReportWidgetBase::secondParent() const
{
    Q_D(const QReportWidgetBase);
    return d->secondParent;
}

void QReportWidgetBase::setSecondParent(QReportBand *widget)
{
    Q_D(QReportWidgetBase);
    d->secondParent = widget;
}

qreal QReportWidgetBase::topAtSecondBand() const
{
    Q_D(const QReportWidgetBase);
    return d->topAtSecondBand;
}

void QReportWidgetBase::setTopAtSecondBand(qreal value)
{
    Q_D(QReportWidgetBase);
    d->topAtSecondBand = value;
}

LEAF_END_NAMESPACE
