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

#ifndef RLINEBASE_H
#define RLINEBASE_H

#include "widgetbase.h"

LEAF_BEGIN_NAMESPACE

class LReportLineBase : public LReportWidgetBase
{
   Q_OBJECT

<<<<<<< HEAD
   REGISTER_PROPERTY_PAGE(line)
=======
   Q_CLASSINFO("prop_line", "true")
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93

   Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true USER true )
   Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor DESIGNABLE true USER true )
   Q_PROPERTY( Qt::PenStyle  lineType READ lineType WRITE setLineType DESIGNABLE true USER true )



    int m_lineWidth;

    QColor m_lineColor;

Qt::PenStyle m_lineType;

public:
    LReportLineBase(QGraphicsItem *parent);

    ~LReportLineBase();

   void loadDom(QDomElement *dom);

   int lineWidth() const;
   QColor lineColor() const;
   Qt::PenStyle lineType() const;

public slots:
   void setLineWidth(int lineWidth);
   void setLineColor(QColor lineColor);
   void setLineType(Qt::PenStyle lineType);
};

LEAF_END_NAMESPACE

#endif
