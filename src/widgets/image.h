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

#ifndef QREPORTIMAGE_H
#define QREPORTIMAGE_H

#include "displaybase.h"

LEAF_BEGIN_NAMESPACE

class LReportImage : public LReportDisplayBase
{
    Q_OBJECT

    REGISTER_PROPERTY_PAGE(image)
    REGISTER_PROPERTY_PAGE(align)

    Q_PROPERTY(QPixmap image       READ image       WRITE setImage       USER true)
    Q_PROPERTY(bool    scaleImage  READ scaleImage  WRITE setScaleImage  USER true)
    Q_PROPERTY(bool    acceptRatio READ acceptRatio WRITE setAcceptRatio USER true)

    QPixmap m_image;
    bool m_scaleImage;
    bool m_acceptRatio;

public:
    LReportImage(QGraphicsItem *parent = 0);
    ~LReportImage();

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *Widget);

    void saveDom(QDomElement *dom);
    void loadDom(QDomElement *dom);
    QPixmap image() const;
    bool scaleImage() const;
    bool acceptRatio() const;

public slots:
    void setImage(QPixmap image);
    void setScaleImage(bool scaleImage);
    void setAcceptRatio(bool acceptRatio);
};

LEAF_END_NAMESPACE

#endif
