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

#include "rectanglebase.h"

#include "propertypages/propertypagepos.h"
#include "propertypages/propertypagerectangle.h"


#include <QDomElement>
#include <QDebug>

LEAF_BEGIN_NAMESPACE

Rectangle::Rectangle(QGraphicsItem *parent):
    WidgetBase(parent)
{
    setResizeDirection( Top | Bottom | Left | Right);

    setFillColor(Qt::white);
    setFillType(Qt::SolidPattern);
    setLineColor(Qt::black);
    setLineWidth(1);
    setLineType(Qt::SolidLine);
}


Rectangle::~Rectangle()
{
}


void Rectangle::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // draw edge lines
    /*
    painter->drawLine( 0,              0,               0,                  5 );
    painter->drawLine( 0,              0,               5,                  0 );
    painter->drawLine( size().width(), 0,               size().width(),     5 );
    painter->drawLine( size().width(), 0,               size().width() - 5, 0 );
    painter->drawLine( 0,              size().height(), 0,                  size().height() - 5 );
    painter->drawLine( 5,              size().height(), 0,                  size().height() );
    painter->drawLine( size().width(), size().height(), size().width(),     size().height() - 5 );
    painter->drawLine( size().width(), size().height(), size().width() - 5, size().height() );
  */

    //fill background
    QBrush brush;
    brush.setStyle(fillType());
    brush.setColor(fillColor());
    painter->setBrush(brush);
    painter->fillRect(this->rect(), fillType());

    //draw border
    QPen pen;
    pen.setStyle(lineType());
    pen.setColor(lineColor());
    pen.setWidth(lineWidth());
    painter->setPen(pen);
    painter->drawRect(this->rect().adjusted(
                          lineWidth() / 2,
                          lineWidth() / 2,
                          -lineWidth() / 2,
                          -lineWidth() / 2));
}



QRectF Rectangle::insideRect() const
{
    if (lineType() == Qt::NoPen)
        return rect();
    else
        return QRectF(lineWidth(),
                      lineWidth(),
                      size().width()  - lineWidth()  *2 + 1,
                      size().height() - lineWidth()  *2 + 1);
}

void Rectangle::loadDom(QDomElement *dom)
{
    WidgetBase::loadDom(dom);

    QColor c;
    int n;

    if (dom->hasAttribute("lineColor")) {
        c = QColor(dom->attribute("lineColor"));
        setLineColor(c);
    }//if
    if (dom->hasAttribute("fillColor")) {
        c = QColor(dom->attribute("fillColor"));
        setFillColor(c);
    }//if
    if (dom->hasAttribute("lineType")) {
        n = QString(dom->attribute("lineType")).toInt();
        setLineType((Qt::PenStyle)n);
    }//if

    if (dom->hasAttribute("fillType")) {
        n = QString(dom->attribute("fillType")).toInt();
        setFillType((Qt::BrushStyle)n);
    }//if
}

void Rectangle::setFillColor(QColor fillColor)
{
    m_fillColor = fillColor;
}

void Rectangle::setFillType(Qt::BrushStyle fillType)
{
    m_fillType = fillType;
}

void Rectangle::setLineType(Qt::PenStyle lineType)
{
    m_lineType = lineType;
}

void Rectangle::setLineColor(QColor lineColor)
{
    m_lineColor = lineColor;
}

void Rectangle::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

Qt::BrushStyle Rectangle::fillType() const
{
    return m_fillType;
}

Qt::PenStyle Rectangle::lineType() const
{
    return m_lineType;
}

QColor Rectangle::lineColor() const
{
    return m_lineColor;
}

int Rectangle::lineWidth() const
{
    return m_lineWidth;
}

QColor Rectangle::fillColor() const
{
    return m_fillColor;
}

LEAF_END_NAMESPACE
