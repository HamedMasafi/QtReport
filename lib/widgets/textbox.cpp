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

#include <QStyleOption>

#include "textbox.h"
#include "propertypages/propertypagetext.h"
#include "propertypages/propertypagepos.h"
#include "propertypages/propertypagerectangle.h"
#include "propertypages/propertypagefont.h"

LEAF_BEGIN_NAMESPACE

TextBox::TextBox(QGraphicsItem *parent) :
    DisplayBase(parent)
{
    this->setSize(90, 40);
    this->setMinimumSize(10, 4);

    setLineWidth(1);
    setLineType(Qt::NoPen);
    setLineColor(Qt::black);

    setFillColor(Qt::white);
    setFillType(Qt::SolidPattern);

    setForeColor(Qt::black);
    setFont(QFont());
    setText(QString::null);
}


TextBox::~TextBox()
{
}


void TextBox::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    Rectangle::paint(painter, option, widget);

    Q_UNUSED(option);
    Q_UNUSED(widget);

    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    textOption.setAlignment(align());

    painter->setFont(font());
    painter->setPen(foreColor());
    painter->drawText(this->rect(),
                      text(),
                      textOption);
}

QColor TextBox::foreColor() const
{
    return m_foreColor;
}

QFont TextBox::font() const
{
    return m_font;
}

QString TextBox::text() const
{
    return m_text;
}

void TextBox::setForeColor(QColor foreColor)
{
    m_foreColor = foreColor;
}

void TextBox::setFont(QFont font)
{
    m_font = font;
}

void TextBox::setText(QString text)
{
    m_text = text;
}

LEAF_END_NAMESPACE
