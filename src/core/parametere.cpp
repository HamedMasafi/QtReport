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


#include <QtCore/QVariant>
#include <QtCore/QString>

#include "parametere.h"

LEAF_BEGIN_NAMESPACE

Parametere::Parametere(QString name, QVariant value, QVariant::Type type):
    SeriazbleObject(),
    m_name(name),
    m_value(value),
    m_type(type)
{
    setObjectName(name);
    setType((int)type);
}

QString Parametere::name() const
{
    return m_name;
}

int Parametere::type() const
{
    return m_type;
}

QVariant Parametere::value() const
{
    return m_value;
}

QVariant Parametere::defaultValue() const
{
    return m_defaultValue;
}

void Parametere::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void Parametere::setType(int type)
{
    m_type = type;
}

void Parametere::setValue(QVariant value)
{
    m_value = value;
}

void Parametere::setDefaultValue(QVariant defaultValue)
{
    m_defaultValue = defaultValue;
}

LEAF_END_NAMESPACE
