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

#include <QSortFilterProxyModel>
#include "designer/documentdesigner.h"
#include "propertypages/propertypagetext.h"
#include "widgets/textbox.h"
#include "core/report.h"
#include "core/reportmodel.h"

LEAF_BEGIN_NAMESPACE

PropertyPageText::PropertyPageText(QWidget *parent) :
    PropertyPageBase(parent)
{
    setupUi(this);
    _title = tr( "Text" );
}

void PropertyPageText::changeEvent(QEvent *e)
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

void PropertyPageText::load()
{
    QSortFilterProxyModel *f = new QSortFilterProxyModel(this);//
    f->setSourceModel(_designer->report()->model());
    f->setFilterRole(ReportModel::TypeRole);
    f->setFilterKeyColumn(0);
    f->setFilterRegExp("3|4|5|6");
    treeView->setModel(f);
    textEdit->setPlainText(_designer->widgetProperty("text").toString());
}

void PropertyPageText::save()
{
   _designer->setWidgetProperty("text", textEdit->toPlainText());
}

LEAF_END_NAMESPACE
