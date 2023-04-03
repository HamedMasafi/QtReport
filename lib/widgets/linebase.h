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

class LineBase : public WidgetBase
{
   Q_OBJECT

   REGISTER_PROPERTY_PAGE(line)

   Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true USER true )
   Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor DESIGNABLE true USER true )
   Q_PROPERTY( Qt::PenStyle  lineType READ lineType WRITE setLineType DESIGNABLE true USER true )



    int m_lineWidth;

    QColor m_lineColor;

Qt::PenStyle m_lineType;

public:
    LineBase(QGraphicsItem *parent);

    ~LineBase();

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
