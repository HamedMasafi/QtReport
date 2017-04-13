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

#include "sectionsproperties.h"
<<<<<<< HEAD
#include "designer/documentdesigner.h"
#include "core/report.h"
=======
#include "documentdesigner.h"
#include "report.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93
#include "widgets/band.h"

LEAF_BEGIN_NAMESPACE

LReportSectionsProperties::LReportSectionsProperties(QWidget *parent,
                                                     LReportDocumentDesigner *designer,
                                                     LReport *report) :
    QDialog(parent),
    _designer(designer),
    _report(report)
{
    setupUi(this);

    for(int i = 0; i < _report->bands()->count(); i++)
        listWidget->addItem(_report->bands()->at(i)->header());

}

void LReportSectionsProperties::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

LEAF_END_NAMESPACE
