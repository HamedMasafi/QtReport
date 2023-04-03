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

#include "seriazbleobject.h"

#include <QtXml/QDomElement>
#include <QtCore/QMetaProperty>

LEAF_BEGIN_NAMESPACE

SeriazbleObject::SeriazbleObject(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief XMLSeriazble::saveDom
 * @param dom
 */
void SeriazbleObject::saveDom(QDomElement *dom)
{
    dom->setAttribute("type", metaObject()->className());

    for (int i = 0; i < metaObject()->propertyCount(); i++) {
        QMetaProperty prop = metaObject()->property(i);

        //if (prop.isUser(this))
        dom->setAttribute(
            prop.name(),
            prop.read(this).toString());
    }//for
}

void SeriazbleObject::loadDom(QDomElement *dom)
{

    for (int i = 0; i < metaObject()->propertyCount(); i++) {
        QMetaProperty prop = metaObject()->property(i);

        if (prop.isUser(this) && dom->hasAttribute(prop.name())) {
            QString domVal = dom->attribute(prop.name(), prop.read(this).toString());

            prop.write(this, QVariant::fromValue(domVal));
        }//if
    }//for

    setObjectName(dom->attribute("objectName"));
}

void SeriazbleObject::copyTo(SeriazbleObject *other)
{
    for (int i = 0; i < metaObject()->propertyCount(); i++) {
        QMetaProperty prop = metaObject()->property(i);
        other->setProperty(prop.name(), prop.read(this));
    }
}

LEAF_END_NAMESPACE
