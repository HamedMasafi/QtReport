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

#ifndef RDISPLAYBASE_H
#define RDISPLAYBASE_H


#include <QFont>

#include "qreportrectanglebase.h"

LEAF_BEGIN_NAMESPACE

/*!
  *This class is base class for all display class that display a thing
  *in a rectangle region such as textbox, image and rectangle
 */
class QReportDisplayBase : public QReportRectangle
{
   Q_OBJECT

   R_PROPERTY( Qt::Alignment, align, align, setAlign, m_align )
   Q_PROPERTY( Qt::Alignment align READ align WRITE setAlign DESIGNABLE true USER true )


   public:
      QReportDisplayBase ( QGraphicsItem *parent = 0 );

      ~QReportDisplayBase();

};

LEAF_END_NAMESPACE

#endif
