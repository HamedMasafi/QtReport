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


#include <QPainter>
#include <QStyleOptionButton>
#include <QStyleOptionToolButton>
#include <QMenu>

#include "qreportcolorpicker.h"

LEAF_BEGIN_NAMESPACE

QColorPicker::QColorPicker(QWidget *parent, bool toolbarMode) :
    QPushButton( parent ), _toolbarMode(toolbarMode)
{
   popup = new QColorPickerPopup( this );
   popup->setVisible(false);
   popup->setObjectName( QString::fromUtf8("popup") );
   popup->setFrameShape(QFrame::StyledPanel);
   popup->setFrameShadow(QFrame::Plain);

   setText("Automatic");

//   setMinimumWidth( _toolbarMode ? 35 : 100 );
   _selectedColor = Qt::black;

   QPixmap icon( 10, 10 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 10, 10, _selectedColor );
   this->setIcon( icon );

   QMetaObject::connectSlotsByName( this );
}


void QColorPicker::paintEvent ( QPaintEvent * )
{
   QStyleOptionButton option;
   option.initFrom( this );

   option.features = QStyleOptionButton::HasMenu;

   option.text = _selectedColor.name();// text();
   QPixmap icon( 10, 10 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 10, 10, _selectedColor );
   this->setIcon( icon );
   option.icon = icon;//();

   QPainter painter ( this );

   style()->drawControl( QStyle::CE_PushButton, &option, &painter, this );
}


void QColorPicker::mouseReleaseEvent ( QMouseEvent * )
{
   popup->move(  this->mapToGlobal( QPoint(0, this->height()) ) );
   popup->setWindowFlags( Qt::Popup );
   popup->show();
}

void QColorPicker::setColor( QColor c )
{
   _selectedColor = c;
   setText(c.name());
   update();
}
QColor QColorPicker::color() const
{
   return _selectedColor;
}

void QColorPicker::on_popup_selected( QColor color )
{
   if(color==QColor())
      setText(tr("Automatic"));
   else
      setText(color.name().toUpper());

   QPixmap icon( 10, 10 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 10, 10, _selectedColor );
   setIcon(icon);

   _selectedColor = color;
   update();
}




//QColorPickerTool
QColorPickerTool::QColorPickerTool(QWidget *parent) :
    QToolButton( parent )
{
   popup = new QColorPickerPopup( this );
   popup->setVisible(false);
   popup->setObjectName( QString::fromUtf8("popup") );
   popup->setFrameShape(QFrame::StyledPanel);
   popup->setFrameShadow(QFrame::Plain);

   //setMinimumWidth( 350 );
   _selectedColor = Qt::black;
   this->setToolButtonStyle( Qt::ToolButtonIconOnly );
   QPixmap icon( 10, 10 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 10, 10, _selectedColor );
   this->setIcon( icon );
this->setArrowType( Qt::DownArrow );
this->setCheckable( false );
this->setToolButtonStyle( Qt::ToolButtonFollowStyle );

   QMetaObject::connectSlotsByName( this );
}



void QColorPickerTool::paintEvent ( QPaintEvent * )
{

   QStyleOptionToolButton option;
   option.initFrom( this );

   option.features = QStyleOptionToolButton::HasMenu;
   //option.state = this->style()->stat

   QPixmap icon( 10, 10 );
   QPainter iconPainter( &icon );
   iconPainter.fillRect( 0, 0, 10, 10, _selectedColor );
   //option.icon = icon;

   QPainter painter ( this );
   //option.text = "COLOR";
   option.text = text();
   //painter.fillRect( 0, 0, 10, 10, _selectedColor );
   //painter.setPen( _selectedColor );
   //painter.drawText( 0 ,20, "A" );
   //this->setIcon( icon );

   style()->drawComplexControl( QStyle::CC_ToolButton, &option, &painter, this );

}


void QColorPickerTool::mouseReleaseEvent ( QMouseEvent * )
{
   popup->move(  this->mapToGlobal( QPoint(0, this->height()) ) );
   popup->setWindowFlags( Qt::Popup );
   popup->show();
}


void QColorPickerTool::on_popup_selected( QColor color )
{
   _selectedColor = color;
   repaint();
}

LEAF_END_NAMESPACE
