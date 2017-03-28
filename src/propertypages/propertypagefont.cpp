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

#include "propertypages/propertypagefont.h"
#include "widgets/textbox.h"
#include "designer/documentdesigner.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPageFont::LReportPropertyPageFont(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    setupUi(this);

    _title = tr("Font");
}

void LReportPropertyPageFont::changeEvent(QEvent *e)
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

void LReportPropertyPageFont::load()
{
   QFont font = _designer->widgetProperty("font").value<QFont>();

   toolButtonBold->setChecked( font.bold() );
   toolButtonItalic->setChecked( font.italic() );
   toolButtonUnderline->setChecked( font.underline() );
   toolButtonStrickout->setChecked( font.strikeOut() );

   fontComboBox->setCurrentFont( font );
   //comboBoxSize->setCurrentIndex( comboBoxSize->find() );

   QString s = QString::number( font.pointSize() );
   comboBoxSize->setCurrentIndex( comboBoxSize->findText(s) );
}

void LReportPropertyPageFont::save()
{
   int size;
   bool ok;
   size = QString(comboBoxSize->currentText()).toInt( &ok );
   if( !ok ) size = 10;

   QFont font;
   font.setFamily( fontComboBox->currentFont().family() );
   font.setBold( toolButtonBold->isChecked() );
   font.setItalic( toolButtonItalic->isChecked() );
   font.setUnderline( toolButtonUnderline->isChecked() );
   font.setStrikeOut( toolButtonStrickout->isChecked() );
   font.setPointSize( size );

   _designer->setWidgetProperty("font", font);
}

LEAF_END_NAMESPACE
