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

#ifndef QREPORTTEXTBOX_H
#define QREPORTTEXTBOX_H

#include "displaybase.h"

LEAF_BEGIN_NAMESPACE

class LReportTextBox : public LReportDisplayBase
{
    Q_OBJECT

    REGISTER_PROPERTY_PAGE(text)
    REGISTER_PROPERTY_PAGE(font)
    REGISTER_PROPERTY_PAGE(align)
    REGISTER_PROPERTY_PAGE(format)

    Q_CLASSINFO("LReportTextBox", "true")

    Q_PROPERTY( QColor foreColor READ foreColor WRITE setForeColor DESIGNABLE true USER true )
    Q_PROPERTY( QFont font READ font WRITE setFont DESIGNABLE true USER true )
    Q_PROPERTY( QString text READ text WRITE setText DESIGNABLE true USER true )

public:
    LReportTextBox ( QGraphicsItem *parent = 0 );

    virtual ~LReportTextBox();


    void paint ( QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget *Widget );


    QColor foreColor() const;
    QFont font() const;
    QString text() const;

public slots:
    void setForeColor(QColor foreColor);
    void setFont(QFont font);
    void setText(QString text);

private:
    QColor m_foreColor;
    QFont m_font;
    QString m_text;
};

LEAF_END_NAMESPACE

Q_DECLARE_METATYPE(LEAF_WRAP_NAMESPACE(LReportTextBox*))

#endif
