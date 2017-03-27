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

#include "propertypages/qreportpropertypagealign.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPageAlign::LReportPropertyPageAlign(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    setupUi(this);
    _title = tr( "Alignment" );
}

void LReportPropertyPageAlign::changeEvent(QEvent *e)
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

void LReportPropertyPageAlign::load()
{
   bool ok;
   int align = _designer->widgetProperty("align").toInt(&ok);

   if(ok)
   {
      alignTL->setChecked(align == (Qt::AlignTop | Qt::AlignLeft));
      alignTC->setChecked(align == (Qt::AlignTop | Qt::AlignHCenter));
      alignTR->setChecked(align == (Qt::AlignTop | Qt::AlignRight));
      alignML->setChecked(align == (Qt::AlignVCenter | Qt::AlignLeft));
      alignMC->setChecked(align == (Qt::AlignCenter));
      alignMR->setChecked(align == (Qt::AlignVCenter | Qt::AlignRight));
      alignBL->setChecked(align == (Qt::AlignBottom | Qt::AlignLeft));
      alignBC->setChecked(align == (Qt::AlignBottom | Qt::AlignHCenter));
      alignBR->setChecked(align == (Qt::AlignBottom | Qt::AlignRight));
   }
}

void LReportPropertyPageAlign::save()
{
   Qt::Alignment align;

   if( alignTL->isChecked() ) align = Qt::AlignTop | Qt::AlignLeft;
   if( alignTC->isChecked() ) align = Qt::AlignTop | Qt::AlignHCenter;
   if( alignTR->isChecked() ) align = Qt::AlignTop | Qt::AlignRight;

   if( alignML->isChecked() ) align = Qt::AlignVCenter | Qt::AlignLeft;
   if( alignMC->isChecked() ) align = Qt::AlignCenter;
   if( alignMR->isChecked() ) align = Qt::AlignVCenter | Qt::AlignRight;

   if( alignBL->isChecked() ) align = Qt::AlignBottom | Qt::AlignLeft;
   if( alignBC->isChecked() ) align = Qt::AlignBottom | Qt::AlignHCenter;
   if( alignBR->isChecked() ) align = Qt::AlignBottom | Qt::AlignRight;

   _designer->setWidgetProperty("align", (int)align);
}

LEAF_END_NAMESPACE
