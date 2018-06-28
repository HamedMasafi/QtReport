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


#include "datatable.h"

#include <QtCore/QDebug>
#include <QtSql/QSqlRecord>
#include <QtXml/QDomElement>

LEAF_BEGIN_NAMESPACE

DataField::DataField(QString name) {
    setObjectName(name);
}

int DataField::type() const
{
    return m_type;
}

QString DataField::filter() const
{
    return m_filter;
}

void DataField::setType(int type)
{
    m_type = type;
}

void DataField::setFilter(QString filter)
{
    m_filter = filter;
}

DataTable::DataTable(QString connectionName) :
    SeriazbleObject(),
    m_connectionName(connectionName)
{
}

void DataTable::remove(DataField *field)
{
    _fields.removeOne(field);
}

void DataTable::clear()
{
    _fields.clear();
}

void DataTable::append(DataField *field)
{
    _fields.append(field);
}

void DataTable::append(QString fieldName)
{
    DataField *f = new DataField(fieldName);
    _fields.append(f);
}

void DataTable::appendRecordFields(QSqlRecord *record)
{
    for (int i = 0; i < record->count(); i++)
        append(record->fieldName(i));
}

QList<DataField*> DataTable::fields() const
{
    return _fields;
}

void DataTable::saveDom(QDomElement *dom)
{
    SeriazbleObject::saveDom(dom);

    foreach(DataField *field, _fields){
        QDomElement elParam = dom->ownerDocument().createElement("Field");
        field->saveDom(&elParam);
        dom->appendChild(elParam);
    }//foreach
}

void DataTable::loadDom(QDomElement *dom)
{
    QDomNodeList fieldsList = dom->elementsByTagName("Field");
    for(int i = 0; i < fieldsList.count(); i++){
        QDomElement el = fieldsList.at(i).toElement();
        DataField *field = new DataField(el.attribute("objectName"));
        field->loadDom(&el);
        _fields.append(field);
    }
    SeriazbleObject::loadDom(dom);
}

QString DataTable::connectionName() const
{
    return m_connectionName;
}

QString DataTable::selectCommand() const
{
    return m_selectCommand;
}

void DataTable::setConnectionName(QString connectionName)
{
    m_connectionName = connectionName;
}

void DataTable::setSelectCommand(QString selectCommand)
{
    m_selectCommand = selectCommand;
}

LEAF_END_NAMESPACE
