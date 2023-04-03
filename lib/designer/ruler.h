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

#ifndef RRULER_H
#define RRULER_H

#include "qtreportglobal.h"

#include <QWidget>

class QFontMetrics;
class QMouseEvent;

LEAF_BEGIN_NAMESPACE

class Ruler : public QWidget
{
	public:


      Ruler ( QWidget *parent, Qt::Orientation direction );
      ~Ruler();
		void paintEvent ( QPaintEvent  *event );
		void mouseMoveEvent ( QMouseEvent  *event );

		/*!
		  *Define ruler direction
		 */
      Qt::Orientation direction() const{ return _direction;}
      //Q_PROPERTY ( Qt::Orientation direction READ direction WRITE setDirection );

      int pixelPerUnit() const { return _pixelPerUnit; }
      int startPos() const { return _startPos; }
      int ruleWidth() const { return _ruleWidth; }
      int startMargin() const { return _startMargin; }
      int endMargin() const { return _endMargin; }

      void setDirection( Qt::Orientation direction );
      void setPixelPerUnit(int v);
      void setStartPos(int v);
      void setRuleWidth(int v);
      void setStartMargin(int v);
      void setEndMargin(int v);

	private:
      Qt::Orientation _direction;
		int _pixelPerUnit;
		int _startPos;
		int _ruleWidth;
		int _startMargin;
      int _endMargin;
		QFontMetrics _fontMetrics;

      /* *
		  *Define resze mode. When user move mouse to body start/end (margin)
		  *the pointer form resize mode and user able to resize margin size.
		  *This resize can be in two form:

		enum ResizeMode
		{
			/// Nothing for resize
         NoResize,
			/// User resize start margin
         ResizeStartMargin,
			/// User resize end margin
         ResizeEndMargin,
      } _resizeMode;*/
};

LEAF_END_NAMESPACE

#endif
