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

#include <QAction>

#include <QButtonGroup>
#include <QComboBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QSpinBox>
#include <QTextBrowser>
#include <QWidget>
#include <QColorDialog>
#include <QGridLayout>

#include "propertypages/propertypagelinetype.h"
#include "designer/documentdesigner.h"
#include "colorpicker.h"
#include "widgets/linebase.h"

LEAF_BEGIN_NAMESPACE

PropertyPageLineType::PropertyPageLineType(QWidget *parent)
   : PropertyPageBase(parent)
{
   gridLayout_2 = new QGridLayout( this );
   gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
   gridLayout = new QGridLayout();
   gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
   labelLineWidth = new QLabel( this );
   labelLineWidth->setObjectName(QString::fromUtf8("labelLineWidth"));
   QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   sizePolicy.setHeightForWidth(labelLineWidth->sizePolicy().hasHeightForWidth());
   labelLineWidth->setSizePolicy(sizePolicy);

   gridLayout->addWidget(labelLineWidth, 0, 0, 1, 1);

   spinBoxWidth = new QSpinBox( this );
   spinBoxWidth->setObjectName(QString::fromUtf8("spinBoxWidth"));
   spinBoxWidth->setValue(1);
   spinBoxWidth->setMinimum( 1 );
   spinBoxWidth->setMaximum( 7 );

   gridLayout->addWidget(spinBoxWidth, 0, 1, 1, 1);

   labelColor = new QLabel( this );
   labelColor->setObjectName(QString::fromUtf8("labelColor"));
   QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
   sizePolicy1.setHorizontalStretch(0);
   sizePolicy1.setVerticalStretch(0);
   sizePolicy1.setHeightForWidth(labelColor->sizePolicy().hasHeightForWidth());
   labelColor->setSizePolicy(sizePolicy1);

   gridLayout->addWidget(labelColor, 1, 0, 1, 1);

   /*
   textBrowserColorBox = new QTextBrowser( this );
   textBrowserColorBox->setObjectName(QString::fromUtf8("textBrowserColorBox"));
   QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Ignored);
   sizePolicy2.setHorizontalStretch(0);
   sizePolicy2.setVerticalStretch(0);
   sizePolicy2.setHeightForWidth(textBrowserColorBox->sizePolicy().hasHeightForWidth());
   textBrowserColorBox->setSizePolicy(sizePolicy2);
   textBrowserColorBox->setMaximumSize(QSize(30, 16777215));
   textBrowserColorBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   gridLayout->addWidget(textBrowserColorBox, 1, 1, 1, 1);
 */


   picker = new QColorPicker( this );

   gridLayout->addWidget(picker, 1, 1, 1, 1);
/*
   pushButtonSelectColor = new QPushButton( this );
   pushButtonSelectColor->setObjectName(QString::fromUtf8("pushButtonSelectColor"));
   pushButtonSelectColor->setMaximumSize(QSize(30, 16777215));

   gridLayout->addWidget(pushButtonSelectColor, 1, 2, 1, 1);
*/
   labelType = new QLabel( this );
   labelType->setObjectName(QString::fromUtf8("labelType"));
   sizePolicy.setHeightForWidth(labelType->sizePolicy().hasHeightForWidth());
   labelType->setSizePolicy(sizePolicy);

   gridLayout->addWidget(labelType, 2, 0, 1, 1);

   comboBoxType = new QComboBox( this );
   comboBoxType->setObjectName(QString::fromUtf8("comboBoxType"));

   gridLayout->addWidget(comboBoxType, 2, 1, 1, 2);


   gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

   horizontalSpacer = new QSpacerItem(97, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

   gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

   verticalSpacer = new QSpacerItem(20, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

   gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);



   this->setWindowTitle(tr("Form"));
   labelLineWidth->setText(tr("Line width:"));
   labelColor->setText(tr("Color:"));
   //pushButtonSelectColor->setText( "..." );
   labelType->setText(tr("Type:"));
   _title = tr( "Line type" );

   QMetaObject::connectSlotsByName( this );


   QPixmap px( 16, 16);
   QPainter painter( &px );

   painter.setPen( Qt::NoPen );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("None"), (int)Qt::NoPen );

   painter.setPen( Qt::SolidLine );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("Solid"), (int)Qt::SolidLine );

   painter.setPen( Qt::DashLine );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("Dash"), (int)Qt::DashLine );

   painter.setPen( Qt::DotLine );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("Dot"), (int)Qt::DotLine );

   painter.setPen( Qt::DashDotLine );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("Dash-Dot"), (int)Qt::DashDotLine );

   painter.setPen( Qt::DashDotDotLine );
   px.fill( Qt::white );
   painter.drawLine( 0, 8, 16, 8 );
   comboBoxType->addItem( QIcon(px), tr("Dash-Dot-Dot"), (int)Qt::DashDotDotLine );

}

void PropertyPageLineType::load()
{
   comboBoxType->setCurrentIndex(_designer->widgetProperty("lineType").toInt());
   picker->setColor(QColor(_designer->widgetProperty("lineColor").toString()));
   spinBoxWidth->setValue( _designer->widgetProperty("lineWidth").toInt() );

   picker->update();
}

void PropertyPageLineType::save()
{
   _designer->setWidgetProperty( "lineColor", picker->color() );
   _designer->setWidgetProperty( "lineType", comboBoxType->currentIndex() );
   _designer->setWidgetProperty( "lineWidth", spinBoxWidth->value() );
}


void PropertyPageLineType::on_pushButtonSelectColor_clicked()
{
   QColorDialog *dlg = new QColorDialog();
   dlg->exec();

   QPalette palette;
   QBrush brush( dlg->currentColor() );
   brush.setStyle(Qt::SolidPattern);
   palette.setBrush(QPalette::Active, QPalette::Base, brush);
   palette.setBrush(QPalette::Inactive, QPalette::Base, brush);

   textBrowserColorBox->setPalette(palette);

   //textBrowserColorBox->palette().setColor( QPalette::Base, dlg->currentColor() );
}

LEAF_END_NAMESPACE
