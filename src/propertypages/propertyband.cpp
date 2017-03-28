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

#include "propertyband.h"
#include "sectiondataproperties.h"

#include "widgets/band.h"
#include "report.h"

LEAF_BEGIN_NAMESPACE

LReportBand *LReportPropertyBand::band() const
{
    return _band;
}

void LReportPropertyBand::setBand(LReportBand *band)
{
    _band = band;
    QWidget *w = 0;

    switch(band->bandType()){
    case ::Data:
        w = new LReportSectionDataProperties();
        qDebug() << "------------------------------";
        break;
    }

    if(w)
        widgetPropertyPage->layout()->addWidget(w);
}
LReportPropertyBand::LReportPropertyBand(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    _title = tr("Band properties");
    setupUi(this);
}

void LReportPropertyBand::load()
{
    foreach (LReportDataTable *table, _designer->report()->dataTables())
        comboBox->addItem(table->objectName());
}

void LReportPropertyBand::save()
{

}

void LReportPropertyBand::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

LEAF_END_NAMESPACE
