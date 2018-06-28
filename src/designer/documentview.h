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

#ifndef RDOCUMENT_H
#define RDOCUMENT_H


#include <QGraphicsView>
#include "qtreportglobal.h"

class QGraphicsSceneMouseEvent;

LEAF_BEGIN_NAMESPACE

class DocumentView : public QGraphicsView
{
       Q_OBJECT

   public:
      DocumentView ( QWidget *parent );

      DocumentView ( QGraphicsScene *scene, QWidget *parent );

      ~DocumentView();

      /*!
        *Set page size for current view in pixle mode.
       * \param width width of page
       * \param heigth heigth of page
     */
      void setPageSize ( int width, int heigth );


   signals:
      void mouseMove ( QGraphicsSceneMouseEvent  *mouseEvent );
      void mousePress ( QGraphicsSceneMouseEvent  *mouseEvent );
      //void mouseRelease ( QGraphicsSceneMouseEvent  *mouseEvent );
      void scroll( int dx, int dy );

   protected:
      void mouseMoveEvent ( QGraphicsSceneMouseEvent  *mouseEvent );
      void mousePressEvent ( QGraphicsSceneMouseEvent  *mouseEvent );
      //void mouseReleaseEvent ( QGraphicsSceneMouseEvent  *mouseEvent );
      void scrollContentsBy ( int dx, int dy );

};

LEAF_END_NAMESPACE

#endif
