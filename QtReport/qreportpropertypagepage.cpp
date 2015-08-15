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


#include "qreportpropertypagepage.h"

#include <QPrinter>
#include <QPageSetupDialog>

QReportPropertyPagePage::QReportPropertyPagePage(QWidget *parent) :
    QWidget(parent)
{
   setupUi(this);

   comboBoxPageSizes->addItem(tr("A0"), QPrinter::A0);
   comboBoxPageSizes->addItem(tr("A1"), QPrinter::A1);
   comboBoxPageSizes->addItem(tr("A2"), QPrinter::A2);
   comboBoxPageSizes->addItem(tr("A3"), QPrinter::A3);
   comboBoxPageSizes->addItem(tr("A4"), QPrinter::A4);
   comboBoxPageSizes->addItem(tr("A5"), QPrinter::A5);
   comboBoxPageSizes->addItem(tr("A6"), QPrinter::A6);
   comboBoxPageSizes->addItem(tr("A7"), QPrinter::A7);
   comboBoxPageSizes->addItem(tr("A8"), QPrinter::A8);
   comboBoxPageSizes->addItem(tr("A9"), QPrinter::A9);
   comboBoxPageSizes->addItem(tr("B0"), QPrinter::B0);
   comboBoxPageSizes->addItem(tr("B1"), QPrinter::B1);
   comboBoxPageSizes->addItem(tr("B2"), QPrinter::B2);
   comboBoxPageSizes->addItem(tr("B3"), QPrinter::B3);
   comboBoxPageSizes->addItem(tr("B4"), QPrinter::B4);
   comboBoxPageSizes->addItem(tr("B5"), QPrinter::B5);
   comboBoxPageSizes->addItem(tr("B6"), QPrinter::B6);
   comboBoxPageSizes->addItem(tr("B7"), QPrinter::B7);
   comboBoxPageSizes->addItem(tr("B8"), QPrinter::B8);
   comboBoxPageSizes->addItem(tr("B9"), QPrinter::B9);
   comboBoxPageSizes->addItem(tr("B10"), QPrinter::B10);
   comboBoxPageSizes->addItem(tr("C5E"), QPrinter::C5E);
   comboBoxPageSizes->addItem(tr("DLE"), QPrinter::DLE);
   comboBoxPageSizes->addItem(tr("Executive"), QPrinter::Executive);
   comboBoxPageSizes->addItem(tr("Folio"), QPrinter::Folio);
   comboBoxPageSizes->addItem(tr("Ledger"), QPrinter::Ledger);
   comboBoxPageSizes->addItem(tr("Legal"), QPrinter::Legal);
   comboBoxPageSizes->addItem(tr("Letter"), QPrinter::Letter);
   comboBoxPageSizes->addItem(tr("Tabloid"), QPrinter::Tabloid);
   comboBoxPageSizes->addItem(tr("US Common #10 Envelope"), QPrinter::Comm10E);
   comboBoxPageSizes->addItem(tr("Custom"), QPrinter::Custom);
}

void QReportPropertyPagePage::changeEvent(QEvent *e)
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
