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
<<<<<<< HEAD
#include "designer/documentdesigner.h"
=======
#include "documentdesigner.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93
#include "propertypages/propertypagebase.h"
#include "widgets/widgetbase.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPageBase::LReportPropertyPageBase(QWidget *parent) :
    QWidget(parent)
{
}


bool LReportPropertyPageBase::isChanged() const
{
   return _isChanged;
}

int LReportPropertyPageBase::index() const
{
   return _index;
}

QString LReportPropertyPageBase::title() const
{
   return _title;
}

LReportDocumentDesigner *LReportPropertyPageBase::designer() const
{
    return _designer;
}

void LReportPropertyPageBase::setDesigner(LReportDocumentDesigner *designer)
{
    _designer = designer;
}

LEAF_END_NAMESPACE

