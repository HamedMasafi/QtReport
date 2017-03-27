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

#ifndef QSECTIONBAND_H
#define QSECTIONBAND_H

#include "qtreportglobal.h"
#include "qreportpanel.h"

LEAF_BEGIN_NAMESPACE

class QReportBand : public QReportPanel
{
    Q_OBJECT

    Q_PROPERTY(qreal headerHeight READ headerHeight WRITE setHeaderHeight USER true)
    Q_PROPERTY(BandType bandType READ bandType WRITE setBandType USER true)
    Q_PROPERTY(qreal bandHeight READ bandHeight WRITE setBandHeight USER true)
    Q_PROPERTY(int index READ index WRITE setIndex USER true)

    Q_CLASSINFO("prop_band", "true")

public:
    QReportBand(QGraphicsItem *parent = 0);
    QReportBand(BandType type, QGraphicsItem *parent = 0);

    ~QReportBand();

    /*!
          *Return top of current band.
       */
    //      qreal top() const;
    void setTop(qreal top);
    //      Q_PROPERTY(qreal top READ top WRITE setTop)


    qreal headerHeight() const;
    void setHeaderHeight(qreal headerHeight);


    BandType  bandType() const;
    void setBandType(BandType type);

    qreal bandHeight() const;
    void setBandHeight(qreal value);

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *Widget);

    void addWidget(QReportWidgetBase*, QPointF);

    QString header() const;
    QString typeString() const;

    void setHeight(int height);
    void setSize(int width, int height);

    void loadDom(QDomElement *dom);
    void saveDom(QDomElement *dom);

    void setIndex(int index);
    int index() const;

private :
    qreal    m_top;
    int      m_index;
    bool     m_printAtBottom;
    qreal    _headerHeight;
    BandType      _bandType;
    QPointF        _childPos;
    int        _index;

};

LEAF_END_NAMESPACE

#endif
