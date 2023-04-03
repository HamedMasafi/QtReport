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

#include <QLabel>

#include "widgets/widgetbase.h"
#include "designer/documentdesigner.h"
#include "propertypages/propertypagebase.h"
#include "widgets/widgetbase.h"

LEAF_BEGIN_NAMESPACE

PropertyPageBase::PropertyPageBase(QWidget *parent) :
    QWidget(parent)
{
}


bool PropertyPageBase::isChanged() const
{
   return _isChanged;
}

int PropertyPageBase::index() const
{
   return _index;
}

QString PropertyPageBase::title() const
{
   return _title;
}

DocumentDesigner *PropertyPageBase::designer() const
{
    return _designer;
}

void PropertyPageBase::setDesigner(DocumentDesigner *designer)
{
    _designer = designer;
}

LEAF_END_NAMESPACE

