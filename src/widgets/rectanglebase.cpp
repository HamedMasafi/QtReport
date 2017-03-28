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

LReportRectangle::LReportRectangle(QGraphicsItem *parent):
    LReportWidgetBase(parent)
{
    setResizeDirection( Top | Bottom | Left | Right);

    setFillColor(Qt::white);
    setFillType(Qt::SolidPattern);
    setLineColor(Qt::black);
    setLineWidth(1);
    setLineType(Qt::SolidLine);
}


LReportRectangle::~LReportRectangle()
{
}


void LReportRectangle::paint(QPainter *painter,
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



QRectF LReportRectangle::insideRect() const
{
    if (lineType() == Qt::NoPen)
        return rect();
    else
        return QRectF(lineWidth(),
                      lineWidth(),
                      size().width()  - lineWidth()  *2 + 1,
                      size().height() - lineWidth()  *2 + 1);
}

void LReportRectangle::loadDom(QDomElement *dom)
{
    LReportWidgetBase::loadDom(dom);

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

void LReportRectangle::setFillColor(QColor fillColor)
{
    m_fillColor = fillColor;
}

void LReportRectangle::setFillType(Qt::BrushStyle fillType)
{
    m_fillType = fillType;
}

void LReportRectangle::setLineType(Qt::PenStyle lineType)
{
    m_lineType = lineType;
}

void LReportRectangle::setLineColor(QColor lineColor)
{
    m_lineColor = lineColor;
}

void LReportRectangle::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

Qt::BrushStyle LReportRectangle::fillType() const
{
    return m_fillType;
}

Qt::PenStyle LReportRectangle::lineType() const
{
    return m_lineType;
}

QColor LReportRectangle::lineColor() const
{
    return m_lineColor;
}

int LReportRectangle::lineWidth() const
{
    return m_lineWidth;
}

QColor LReportRectangle::fillColor() const
{
    return m_fillColor;
}

LEAF_END_NAMESPACE
