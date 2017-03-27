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

#include "qreportverticalline.h"

LEAF_BEGIN_NAMESPACE

QReportVerticalLine::QReportVerticalLine(QGraphicsItem *parent): QReportLineBase(parent)
{
   this->setResizeDirection( ::Left | ::Right );
   this->setHeight( 7 );
   this->setWidth( 90 );
   this->setMarginPos( 0, 4 );
   setFixedSize(0, 7);
}


QReportVerticalLine::~QReportVerticalLine()
{
}

void QReportVerticalLine::paint ( QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget )
{
  Q_UNUSED( option );
  Q_UNUSED( widget );
  
  QPen pen;
  pen.setStyle( lineType() );
  pen.setColor( lineColor() );
  pen.setWidth( lineWidth() );
  painter->setPen( pen );
  painter->drawLine( 0,
                     4,
                     this->boundingRect().width(), 
                     4 );

}

LEAF_END_NAMESPACE