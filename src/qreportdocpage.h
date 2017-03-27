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


#ifndef RDOCPAGE_H
#define RDOCPAGE_H


class QGraphicsSceneMouseEvent;

#include "widgets/qreportwidgetbase.h"

LEAF_BEGIN_NAMESPACE

class Q_DECL_HIDDEN LReportPage : public LReportWidgetBase
{
   public:
      LReportPage( QGraphicsItem *parent=0 );

      ~LReportPage();

      void paint ( QPainter  *painter, const QStyleOptionGraphicsItem  *option, QWidget  *Widget = 0 )  ;

      void setMargins ( qreal left, qreal top, qreal Right, qreal Bottom );
      void setGridSize( qreal gridSize);

      Q_PROPERTY ( int gridSize READ gridSize WRITE setGridSize )

      QRect documentArea() const;

      GridType gridType() const{ return _gridType; }
      void setGridType( GridType type ){ _gridType = type; }

      void mousePressEvent( QGraphicsSceneMouseEvent  *event );

   private:
      GridType _gridType;
      int _gridSize;
      qreal _marginLeft;
      qreal _marginBottom;
      qreal _marginTop;
      qreal _marginRight;
};

LEAF_END_NAMESPACE

#endif
