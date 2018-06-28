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


#include "propertypages/propertypagerectangle.h"
#include "designer/documentdesigner.h"
#include "colorpicker.h"
#include "widgets/rectanglebase.h"

LEAF_BEGIN_NAMESPACE

PropertyPageRectangle::PropertyPageRectangle(QWidget *parent) :
    PropertyPageBase(parent)
{
    setupUi(this);

     _title = tr( "Rectangle" );

    QPixmap px( 16, 16);
    QPainter painter( &px );

    painter.setPen( Qt::NoPen );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("None"), (int)Qt::NoPen );

    painter.setPen( Qt::SolidLine );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("Solid"), (int)Qt::SolidLine );

    painter.setPen( Qt::DashLine );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("Dash"), (int)Qt::DashLine );

    painter.setPen( Qt::DotLine );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("Dot"), (int)Qt::DotLine );

    painter.setPen( Qt::DashDotLine );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("Dash-Dot"), (int)Qt::DashDotLine );

    painter.setPen( Qt::DashDotDotLine );
    px.fill( Qt::white );
    painter.drawLine( 0, 8, 16, 8 );
    comboBoxLineType->addItem( QIcon(px), tr("Dash-Dot-Dot"), (int)Qt::DashDotDotLine );

    pickerLineColor = new QColorPicker( this );
    pickerFillColor = new QColorPicker( this );

    formLayout->setWidget( 1, QFormLayout::FieldRole, pickerLineColor );
    formLayout->setWidget( 4, QFormLayout::FieldRole, pickerFillColor );
}

void PropertyPageRectangle::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
       case QEvent::LanguageChange:
           retranslateUi(this);
           break;
       default:
           break;
    }
}


void PropertyPageRectangle::load()
{
   comboBoxLineType->setCurrentIndex(_designer->widgetProperty("lineType").toInt());
   pickerLineColor->setColor(QColor(_designer->widgetProperty("lineColor").toString()));
   pickerFillColor->setColor(QColor(_designer->widgetProperty("fillColor").toString()));
   spinBoxLineWidth->setValue( _designer->widgetProperty("lineWidth").toInt() );

   pickerFillColor->update();
   pickerLineColor->update();
}

void PropertyPageRectangle::save()
{
   _designer->setWidgetProperty("fillType", (int)Qt::SolidPattern );
   _designer->setWidgetProperty("lineType",
                                comboBoxLineType->itemData( comboBoxLineType->currentIndex() ).toInt() );

   _designer->setWidgetProperty("lineColor", pickerLineColor->color().name());
   _designer->setWidgetProperty("fillColor", pickerFillColor->color().name());
   _designer->setWidgetProperty("lineWidth", spinBoxLineWidth->value());
}

LEAF_END_NAMESPACE
