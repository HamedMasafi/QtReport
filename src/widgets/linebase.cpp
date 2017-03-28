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

LReportLineBase::LReportLineBase(QGraphicsItem *parent): LReportWidgetBase(parent)
{
   setLineWidth( 1 );
   setLineType( Qt::SolidLine );
   setLineColor( Qt::black );
}


LReportLineBase::~LReportLineBase()
{
}

void LReportLineBase::loadDom(QDomElement *dom)
{
    LReportWidgetBase::loadDom(dom);

    if (dom->hasAttribute("lineType")) {
        int n = QString(dom->attribute("lineType")).toInt();
        setLineType((Qt::PenStyle)n);
    }//if
}

int LReportLineBase::lineWidth() const
{
    return m_lineWidth;
}

QColor LReportLineBase::lineColor() const
{
    return m_lineColor;
}

Qt::PenStyle LReportLineBase::lineType() const
{
    return m_lineType;
}

void LReportLineBase::setLineWidth(int lineWidth)
{
    m_lineWidth = lineWidth;
}

void LReportLineBase::setLineColor(QColor lineColor)
{
    m_lineColor = lineColor;
}

void LReportLineBase::setLineType(Qt::PenStyle lineType)
{
    m_lineType = lineType;
}


LEAF_END_NAMESPACE
