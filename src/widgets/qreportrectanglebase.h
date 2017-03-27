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

#include "qreportwidgetbase.h"

LEAF_BEGIN_NAMESPACE

class LReportRectangle : public LReportWidgetBase
{
   Q_OBJECT

   Q_CLASSINFO("prop_rect", "true")

   R_PROPERTY( int,            lineWidth, lineWidth, setLineWidth, m_lineWidth )
   Q_PROPERTY( int lineWidth READ lineWidth WRITE setLineWidth DESIGNABLE true USER true )

   R_PROPERTY( QColor,         lineColor, lineColor, setLineColor, m_lineColor )
   Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor DESIGNABLE true USER true )

   R_PROPERTY( Qt::PenStyle,   lineType,  lineType,  setLineType,  m_lineType  )
   Q_PROPERTY( Qt::PenStyle  lineType READ lineType WRITE setLineType DESIGNABLE true USER true )

   R_PROPERTY( Qt::BrushStyle, fillType,  fillType,  setFillType,  m_fillType )
   Q_PROPERTY( Qt::BrushStyle fillType READ fillType WRITE setFillType  DESIGNABLE true USER true)

   R_PROPERTY( QColor,         fillColor, fillColor, setFillColor, m_fillColor )
   Q_PROPERTY( QColor fillColor READ fillColor WRITE setFillColor DESIGNABLE true USER true )


   public:
      LReportRectangle ( QGraphicsItem *parent = 0 );
      ~LReportRectangle();

      void paint ( QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *Widget );


      QRectF insideRect() const;

      QString _sample;
      QString sample() const{ return _sample; }
      void setSample( QString v ){ _sample = v; }


      void loadDom( QDomElement *dom );

};

LEAF_END_NAMESPACE

#endif
