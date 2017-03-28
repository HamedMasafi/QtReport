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

#ifndef RRECTANGLEBASE_H
#define RRECTANGLEBASE_H

#include "widgetbase.h"

LEAF_BEGIN_NAMESPACE

class LReportRectangle : public LReportWidgetBase
{
    Q_OBJECT

    REGISTER_PROPERTY_PAGE(rect)

    Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true USER true )
    Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor DESIGNABLE true USER true )
    Q_PROPERTY( Qt::PenStyle  lineType READ lineType WRITE setLineType DESIGNABLE true USER true )
    Q_PROPERTY( Qt::BrushStyle fillType READ fillType WRITE setFillType  DESIGNABLE true USER true)
    Q_PROPERTY( QColor fillColor READ fillColor WRITE setFillColor DESIGNABLE true USER true )


    int m_lineWidth;
    QColor m_lineColor;
    Qt::PenStyle m_lineType;
    Qt::BrushStyle m_fillType;
    QColor m_fillColor;

public:
    LReportRectangle ( QGraphicsItem *parent = 0 );
    ~LReportRectangle();

    void paint ( QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *Widget );

    QRectF insideRect() const;

    void loadDom( QDomElement *dom );

    int lineWidth() const;
    QColor lineColor() const;
    Qt::PenStyle lineType() const;
    Qt::BrushStyle fillType() const;
    QColor fillColor() const;

public slots:
    void setLineWidth(int lineWidth);
    void setLineColor(QColor lineColor);
    void setLineType(Qt::PenStyle lineType);
    void setFillType(Qt::BrushStyle fillType);
    void setFillColor(QColor fillColor);
};

LEAF_END_NAMESPACE

#endif
