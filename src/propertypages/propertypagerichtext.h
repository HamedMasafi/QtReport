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


#ifndef RPROPERTYPAGERICHTEXT_H
#define RPROPERTYPAGERICHTEXT_H

#include "propertypages/propertypagebase.h"
<<<<<<< HEAD
#include "ui_propertypagerichtext.h"
=======
#include "ui_qreportpropertypagerichtext.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93

LEAF_BEGIN_NAMESPACE

class LReportPropertyPageRichText : public LReportPropertyPageBase, private Ui::LReportPropertyPageRichText
{
    Q_OBJECT

public:
    LReportPropertyPageRichText(QWidget *parent = 0);

    void save(LReportWidgetBase *);
    void load(LReportWidgetBase *);

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // RPROPERTYPAGERICHTEXT_H
