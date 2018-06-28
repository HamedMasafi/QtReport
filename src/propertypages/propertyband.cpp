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
#include "core/report.h"

LEAF_BEGIN_NAMESPACE

Band *PropertyBand::band() const
{
    return _band;
}

void PropertyBand::setBand(Band *band)
{
    _band = band;
    QWidget *w = 0;

    switch(band->bandType()){
    case ::Data:
        w = new SectionDataProperties();
        qDebug() << "------------------------------";
        break;
    }

    if(w)
        widgetPropertyPage->layout()->addWidget(w);
}
PropertyBand::PropertyBand(QWidget *parent) :
    PropertyPageBase(parent)
{
    _title = tr("Band properties");
    setupUi(this);
}

void PropertyBand::load()
{
    foreach (DataTable *table, _designer->report()->dataTables())
        comboBox->addItem(table->objectName());
}

void PropertyBand::save()
{

}

void PropertyBand::changeEvent(QEvent *e)
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
