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

#include <QDomElement>

#include "propertypages/propertypagepos.h"
#include "propertypages/propertypagelinetype.h"
#include "linebase.h"

LEAF_BEGIN_NAMESPACE

LineBase::LineBase(QGraphicsItem *parent): WidgetBase(parent)
{
   setLineWidth( 1 );
   setLineType( Qt::SolidLine );
   setLineColor( Qt::black );
}


LineBase::~LineBase()
{
}

void LineBase::loadDom(QDomElement *dom)
{
    WidgetBase::loadDom(dom);

    if (dom->hasAttribute("lineType")) {
        int n = QString(dom->attribute("lineType")).toInt();
        setLineType((Qt::PenStyle)n);
    }//if
}

int LineBase::lineWidth() const
{
    return m_lineWidth;
}

QColor LineBase::lineColor() const
{
    return m_lineColor;
}

Qt::PenStyle LineBase::lineType() const
{
    return m_lineType;
}

void LineBase::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

void LineBase::setLineColor(QColor lineColor)
{
    m_lineColor = lineColor;
}

void LineBase::setLineType(Qt::PenStyle lineType)
{
    m_lineType = lineType;
}


LEAF_END_NAMESPACE
