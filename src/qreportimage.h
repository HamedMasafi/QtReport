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

#include "qreportdisplaybase.h"

/*!
   @author Hamed Masafi <Hamed.Masafi@GMail.COM>
*/
class QReportImage : public QReportDisplayBase
{
        Q_OBJECT

        Q_CLASSINFO("prop_image", "true")
        Q_CLASSINFO("prop_align", "true")

        Q_PROPERTY(QPixmap image       READ image       WRITE setImage       USER true)
        Q_PROPERTY(bool    scaleImage  READ scaleImage  WRITE setScaleImage  USER true)
        Q_PROPERTY(bool    acceptRatio READ acceptRatio WRITE setAcceptRatio USER true)

        R_PROPERTY(QPixmap,       image,       image,       setImage,       m_image)
        R_PROPERTY(bool,          scaleImage,  scaleImage,  setScaleImage,  m_scaleImage)
        R_PROPERTY(bool,          acceptRatio, acceptRatio, setAcceptRatio, m_acceptRatio)

    public:
        QReportImage(QGraphicsItem *parent = 0);
        ~QReportImage();

        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *Widget);

        void saveDom(QDomElement *dom);
        void loadDom(QDomElement *dom);
};

#endif
