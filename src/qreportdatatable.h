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


#ifndef RREPORTDATATABLE_H
#define RREPORTDATATABLE_H

#include "qtreportglobal.h"
#include "qreportxmlseriazble.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

class QSqlRecord;

LEAF_BEGIN_NAMESPACE

class LReportDataConnection;
class LReportDataField : public LReportXMLSeriazble
{
    Q_OBJECT

    Q_PROPERTY(int type READ type WRITE setType USER true)
    Q_PROPERTY(QString filter READ filter WRITE setFilter USER true)

    R_PROPERTY(QString, filter, filter, setFilter, _filter)
    R_PROPERTY(int, type, type, setType, _type)

public:
    LReportDataField(QString name) {
        setObjectName(name);
    }
};

class LReportDataTable : public LReportXMLSeriazble
{
    Q_OBJECT

    Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName USER true)
    R_PROPERTY(QString, connectionName, connectionName, setConnectionName, _connectionName)

    Q_PROPERTY(QString selectCommand READ selectCommand WRITE setSelectCommand USER true)
    R_PROPERTY(QString, selectCommand, selectCommand, setSelectCommand, _selectCommand)

    public:
        LReportDataTable(QString connectionName);

        void remove(LReportDataField *field);
        void clear();
        void append(LReportDataField *field);
        void append(QString fieldName);

        void appendRecordFields(QSqlRecord *record);

        QList<LReportDataField*> fields() const;

        void saveDom(QDomElement *dom);
        void loadDom(QDomElement *dom);

    private:
        QList<LReportDataField*> _fields;

};

LEAF_END_NAMESPACE

#endif // RREPORTDATATABLE_H
