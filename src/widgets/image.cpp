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

Image::Image(QGraphicsItem *parent):
    DisplayBase(parent)
{
    setScaleImage(false);
    setAcceptRatio(false);
}


Image::~Image()
{
}



void Image::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    Rectangle::paint(painter, option, widget);

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

void Image::saveDom(QDomElement *dom)
{
    SeriazbleObject::saveDom(dom);

    QByteArray ba;
    QBuffer buffer(&ba, this);
    buffer.open(QIODevice::WriteOnly);

    m_image.save(&buffer, "PNG");

    dom->setAttribute("imageData", QString(ba.toBase64()));
}

void Image::loadDom(QDomElement *dom)
{
    WidgetBase::loadDom(dom);
    QByteArray b;

    b.append(dom->attribute("imageData"));
    m_image.loadFromData(QByteArray::fromBase64(b));
}

QPixmap Image::image() const
{
    return m_image;
}

bool Image::scaleImage() const
{
    return m_scaleImage;
}

bool Image::acceptRatio() const
{
    return m_acceptRatio;
}

void Image::setImage(QPixmap image)
{
    m_image = image;
}

void Image::setScaleImage(bool scaleImage)
{
    m_scaleImage = scaleImage;
}

void Image::setAcceptRatio(bool acceptRatio)
{
    m_acceptRatio = acceptRatio;
}



LEAF_END_NAMESPACE
