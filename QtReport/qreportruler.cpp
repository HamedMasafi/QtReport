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
#include <QFont>
#include <QFontMetrics>
#include <QMouseEvent>


#include <math.h>
#include "qreportruler.h"


/*!
 * \class RRuler
  *Define a new ruler.
 */

QReportRuler::QReportRuler ( QWidget *parent, Qt::Orientation direction ) : QWidget ( parent, 0 )
		, _fontMetrics ( this->font() )
{
   _pixelPerUnit = 0;
   _startPos     = 0;
   _ruleWidth    = 0;
   _startMargin  = 0;
   _endMargin    = 0;

   if ( direction == Qt::Horizontal ) this->setMinimumHeight ( 14 );
   if ( direction == Qt::Vertical )   this->setMinimumWidth ( 14 );

	QFont font ( this->font() );
   font.setPointSize ( 6 );
	this->setFont ( font );
   _fontMetrics = QFontMetrics( this->font() );

   _direction = direction;
	this->setMouseTracking ( true );
}


QReportRuler::~QReportRuler()
{
}


void QReportRuler::paintEvent ( QPaintEvent * )
{
	QPainter p ( this );

	int textHeight = _fontMetrics.height();

   if ( _direction == Qt::Horizontal )
	{
      p.fillRect (
          QRect ( _startPos, 0,
                  _startMargin + _ruleWidth - _endMargin, this->height() ),
          Qt::gray );

      p.fillRect ( QRect ( _startPos + _startMargin, 0,
                           _ruleWidth - _endMargin - _startMargin, this->height() ),
		             Qt::white );

      int startStep = ( _startMargin + _startPos ) %  _pixelPerUnit;
      startStep = startStep - _pixelPerUnit;

      for ( int i  = startStep; i <= _startPos + _ruleWidth; i += _pixelPerUnit )
		{
			QString s;
         if ( i < _startPos )
            s = QString::number ( ( i - _startMargin - _startPos ) / _pixelPerUnit + 1 );
			else
            s = QString::number ( ( i - _startMargin - _startPos ) / _pixelPerUnit );


			int textWidth = _fontMetrics.width ( s );

			QRectF rcPart ( i - textWidth, ( this->height() - textHeight ) / 2,
                            textWidth  *2,     textHeight );

			if ( s != "0" )
				p.drawText ( rcPart, s, Qt::AlignHCenter | Qt::AlignVCenter );

         p.drawLine ( i + ( _pixelPerUnit / 2 ) ,          rcPart.top(),
                      i + ( _pixelPerUnit / 2 ),           rcPart.bottom() );

         int oneFour = _pixelPerUnit / 4;
			p.drawPoint ( i + oneFour, this->height() / 2 );
            p.drawPoint ( i + oneFour  *3, this->height() / 2 );
		}//for

      p.fillRect( 0, 0, _startPos, this->height(), palette().background() );
      p.fillRect( _startPos + _ruleWidth, 0,
                  width() - _startPos - _ruleWidth, this->height(),
                  palette().background() );
	}//if

   if ( _direction == Qt::Vertical )
   {
      p.fillRect (
          QRect ( 0, _startPos,
                  this->height(), _startMargin + _ruleWidth - _endMargin ),
          Qt::gray );

      p.fillRect ( QRect ( 0, _startPos + _startMargin,
                           this->width(), _ruleWidth - _endMargin - _startMargin ),
                   Qt::white );

      int startStep = ( _startMargin + _startPos ) %  _pixelPerUnit;
      startStep = startStep - _pixelPerUnit;

      for ( int i  = startStep; i <= _startPos + _ruleWidth; i += _pixelPerUnit )
      {
         QString s;
         if ( i < _startPos )
            s = QString::number ( ( i - _startMargin - _startPos ) / _pixelPerUnit + 1 );
         else
            s = QString::number ( ( i - _startMargin - _startPos ) / _pixelPerUnit );


         int textWidth = _fontMetrics.width ( s );

         QRectF rcPart ( (this->width() - textWidth) / 2, i - textHeight,
                         textWidth,    textHeight  *2 );

         if ( s != "0" )
            p.drawText ( rcPart, s, Qt::AlignHCenter | Qt::AlignVCenter );

         p.drawLine ( rcPart.left(),  i + ( _pixelPerUnit / 2 ),
                      rcPart.right(), i + ( _pixelPerUnit / 2 ) );

         int oneFour = _pixelPerUnit / 4;
         p.drawPoint ( this->width() / 2, i + oneFour );
         p.drawPoint ( this->width() / 2, i + oneFour  *3 );
      }//for

      p.fillRect( 0, 0, this->width(), _startPos, palette().background() );
      p.fillRect( 0, _startPos + _ruleWidth,
                  this->width(), this->height() - _startPos - _ruleWidth,
                  palette().background() );
   }//if

	//p.drawRect( this->rect() );
}


void QReportRuler::mouseMoveEvent ( QMouseEvent * )
{
   /* not in current plan :)
   _resizeMode = NoResize;

	if ( abs ( event->x() -  _startPos - _startMargin) < 3 )
      _resizeMode = ResizeStartMargin;

	if ( abs ( event->x() -  _startPos - _startMargin - _ruleWidth) < 3 )
     _resizeMode = ResizeEndMargin;
	  
   if( _resizeMode != NoResize )
	   this->setCursor( Qt::SizeHorCursor );
	else
	   this->setCursor( Qt::ArrowCursor );
*/
}


void QReportRuler::setDirection( Qt::Orientation direction )
{
   _direction = direction;

}

void QReportRuler::setPixelPerUnit(int v)
{
   _pixelPerUnit = v;

}

void QReportRuler::setStartPos(int v)
{
   _startPos = v;

}

void QReportRuler::setRuleWidth(int v)
{
   _ruleWidth = v;

}

void QReportRuler::setStartMargin(int v)
{
   _startMargin = v;

}


void QReportRuler::setEndMargin(int v)
{
   _endMargin = v;

}
