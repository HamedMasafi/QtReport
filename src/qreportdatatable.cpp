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

QReportDataTable::QReportDataTable(QString connectionName) :
    QReportXMLSeriazble(),
    _connectionName(connectionName)
{
}

void QReportDataTable::remove(QReportDataField *field)
{
    _fields.removeOne(field);
}

void QReportDataTable::clear()
{
    _fields.clear();
}

void QReportDataTable::append(QReportDataField *field)
{
    _fields.append(field);
}

void QReportDataTable::append(QString fieldName)
{
    QReportDataField *f = new QReportDataField(fieldName);
    _fields.append(f);
}

void QReportDataTable::appendRecordFields(QSqlRecord *record)
{
    for (int i = 0; i < record->count(); i++)
        append(record->fieldName(i));
}

QList<QReportDataField*> QReportDataTable::fields() const
{
    return _fields;
}

void QReportDataTable::saveDom(QDomElement *dom)
{
    QReportXMLSeriazble::saveDom(dom);

    foreach(QReportDataField *field, _fields){
        QDomElement elParam = dom->ownerDocument().createElement("Field");
        field->saveDom(&elParam);
        dom->appendChild(elParam);
    }//foreach
}

void QReportDataTable::loadDom(QDomElement *dom)
{
    QDomNodeList fieldsList = dom->elementsByTagName("Field");
    for(int i = 0; i < fieldsList.count(); i++){
        QDomElement el = fieldsList.at(i).toElement();
        QReportDataField *field = new QReportDataField(el.attribute("objectName"));
        field->loadDom(&el);
        _fields.append(field);
    }
    QReportXMLSeriazble::loadDom(dom);
}

LEAF_END_NAMESPACE
