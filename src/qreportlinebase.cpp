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

#include "qreportpropertypagepos.h"
#include "qreportpropertypagelinetype.h"
#include "qreportlinebase.h"

QReportLineBase::QReportLineBase(QGraphicsItem *parent): QReportWidgetBase(parent)
{
   setLineWidth( 1 );
   setLineType( Qt::SolidLine );
   setLineColor( Qt::black );
}


QReportLineBase::~QReportLineBase()
{
}

void QReportLineBase::loadDom(QDomElement *dom)
{
    QReportWidgetBase::loadDom(dom);

    if (dom->hasAttribute("lineType")) {
        int n = QString(dom->attribute("lineType")).toInt();
        setLineType((Qt::PenStyle)n);
    }//if
}



