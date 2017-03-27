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


#include "qreportdatatable.h"

#include <QtCore/QDebug>
#include <QtSql/QSqlRecord>
#include <QtXml/QDomElement>

LEAF_BEGIN_NAMESPACE

LReportDataTable::LReportDataTable(QString connectionName) :
    LReportXMLSeriazble(),
    _connectionName(connectionName)
{
}

void LReportDataTable::remove(LReportDataField *field)
{
    _fields.removeOne(field);
}

void LReportDataTable::clear()
{
    _fields.clear();
}

void LReportDataTable::append(LReportDataField *field)
{
    _fields.append(field);
}

void LReportDataTable::append(QString fieldName)
{
    LReportDataField *f = new LReportDataField(fieldName);
    _fields.append(f);
}

void LReportDataTable::appendRecordFields(QSqlRecord *record)
{
    for (int i = 0; i < record->count(); i++)
        append(record->fieldName(i));
}

QList<LReportDataField*> LReportDataTable::fields() const
{
    return _fields;
}

void LReportDataTable::saveDom(QDomElement *dom)
{
    LReportXMLSeriazble::saveDom(dom);

    foreach(LReportDataField *field, _fields){
        QDomElement elParam = dom->ownerDocument().createElement("Field");
        field->saveDom(&elParam);
        dom->appendChild(elParam);
    }//foreach
}

void LReportDataTable::loadDom(QDomElement *dom)
{
    QDomNodeList fieldsList = dom->elementsByTagName("Field");
    for(int i = 0; i < fieldsList.count(); i++){
        QDomElement el = fieldsList.at(i).toElement();
        LReportDataField *field = new LReportDataField(el.attribute("objectName"));
        field->loadDom(&el);
        _fields.append(field);
    }
    LReportXMLSeriazble::loadDom(dom);
}

LEAF_END_NAMESPACE
