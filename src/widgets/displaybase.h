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

#include "widgets/rectanglebase.h"

LEAF_BEGIN_NAMESPACE

/*!
  *This class is base class for all display class that display a thing
  *in a rectangle region such as textbox, image and rectangle
 */
class DisplayBase : public Rectangle
{
    Q_OBJECT

    Q_PROPERTY( Qt::Alignment align READ align WRITE setAlign DESIGNABLE true USER true )

    Qt::Alignment m_align;

public:
    DisplayBase ( QGraphicsItem *parent = 0 );

    ~DisplayBase();

    Qt::Alignment align() const;
public slots:
    void setAlign(Qt::Alignment align);
};

LEAF_END_NAMESPACE

#endif
