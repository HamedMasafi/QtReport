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
#include "xmlseriazble.h"

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

    int m_type;
    QString m_filter;

public:
    LReportDataField(QString name);

    int type() const;
    QString filter() const;

public slots:
    void setType(int type);
    void setFilter(QString filter);
};

class LReportDataTable : public LReportXMLSeriazble
{
    Q_OBJECT

    Q_PROPERTY(QString connectionName READ connectionName WRITE setConnectionName USER true)
    Q_PROPERTY(QString selectCommand READ selectCommand WRITE setSelectCommand USER true)

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

    QString connectionName() const;

    QString selectCommand() const;

public slots:
    void setConnectionName(QString connectionName);

    void setSelectCommand(QString selectCommand);

private:
    QList<LReportDataField*> _fields;

    QString m_connectionName;
    QString m_selectCommand;
};

LEAF_END_NAMESPACE

#endif // RREPORTDATATABLE_H
