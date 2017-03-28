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

#include "image.h"

#include "propertypages/propertypagepos.h"
#include "propertypages/propertypagerectangle.h"
#include "propertypages/propertypageimage.h"

#include <QDomElement>
#include <QBuffer>
#include <QDebug>

LEAF_BEGIN_NAMESPACE

LReportImage::LReportImage(QGraphicsItem *parent):
    LReportDisplayBase(parent)
{
    setScaleImage(false);
    setAcceptRatio(false);
}


LReportImage::~LReportImage()
{
}



void LReportImage::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    LReportRectangle::paint(painter, option, widget);

    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (image().isNull()) return;

    if (scaleImage()) {
        if (acceptRatio()) {
            QPixmap pix = image().scaled(insideRect().width(), insideRect().height(),
                                         Qt::KeepAspectRatio);

            painter->drawPixmap(
                        insideRect().x() + (insideRect().width() - pix.width()) / 2,
                        insideRect().y() + (insideRect().height() - pix.height()) / 2,
                        pix);
        } else {
            painter->drawPixmap(insideRect().x(),
                                insideRect().y(),
                                image().scaled(insideRect().width(), insideRect().height(),
                                               Qt::IgnoreAspectRatio));
        }//else
    } else {
        painter->drawPixmap(insideRect(),
                            image(),
                            insideRect());
    }//else

}

void LReportImage::saveDom(QDomElement *dom)
{
    LReportXMLSeriazble::saveDom(dom);

    QByteArray ba;
    QBuffer buffer(&ba, this);
    buffer.open(QIODevice::WriteOnly);

    m_image.save(&buffer, "PNG");

    dom->setAttribute("imageData", QString(ba.toBase64()));
}

void LReportImage::loadDom(QDomElement *dom)
{
    LReportWidgetBase::loadDom(dom);
    QByteArray b;

    b.append(dom->attribute("imageData"));
    m_image.loadFromData(QByteArray::fromBase64(b));
}

QPixmap LReportImage::image() const
{
    return m_image;
}

bool LReportImage::scaleImage() const
{
    return m_scaleImage;
}

bool LReportImage::acceptRatio() const
{
    return m_acceptRatio;
}

void LReportImage::setImage(QPixmap image)
{
    m_image = image;
}

void LReportImage::setScaleImage(bool scaleImage)
{
    m_scaleImage = scaleImage;
}

void LReportImage::setAcceptRatio(bool acceptRatio)
{
    m_acceptRatio = acceptRatio;
}



LEAF_END_NAMESPACE
