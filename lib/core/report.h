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
#ifndef QREPORT_H
#define QREPORT_H

#include <QObject>
#include <QSqlQuery>

#include "qtreportglobal.h"
#include "datatable.h"

template <typename T> class QList;
template <class Key, class T> class QHash;
class QSizeF;
class QSizeF;
class QVariant;
class QString;

LEAF_BEGIN_NAMESPACE

class ReportModel;
class Parametere;
class ReportPrivate;
class WidgetBase;
class Band;
class DataConnection;
class PrintSettings;
class LEAF_EXPORT Report : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath USER true)

public:

    enum XmlNodeType{
        WidgetType      = 1,
        BandType        = 2,
        ConnectionType  = 4,
        DataTableType   = 8,
        ParametereType  = 16,
        All         = WidgetType | BandType | ConnectionType | DataTableType | ParametereType
    };

    Report();

    bool load(QString path);
    void save(QString path = "");

    QByteArray getXmlContent(int NodeFlags = All) const;


    QList<Band *> *bands();
    QList<WidgetBase *> *widgets();

    // designer
    void removeBand(QString name);
    void removeWidget(QString name);

    void widgetToBack(WidgetBase*);
    void widgetToFront(WidgetBase*);
    void bandToBack(Band*);
    void bandToFront(Band*);

    void changeParent(WidgetBase*, Band*);

    // print
    void setParametereValue(QString name, QVariant value);

    QString filePath() const;



    //todo: return one object
    ReportModel *model() const;

    QList<DataTable*> dataTablesByName(QString tableName);
    QList<DataTable*> dataTablesByConnections(QString connectionName);
    QList<DataTable*> dataTables();

    void addDataTable(DataTable *table);
    DataTable *dataTable(QString tableName);
    DataTable *dataTable(QString tableName, QString connectionName);
    void removeDataTable(DataTable *table);

    Band *section(QString sectionName);
    Band *findBandByName(QString bandName);
    DataConnection *findConnectionByName(QString connectionName);
    WidgetBase *findWidgetByName(QString widgetName);

    Parametere *parameter(QString name);
    QList<Parametere*> parameters();
    void addParametere(QString name, QVariant value);
    void addParametere(Parametere *param);
    void removeParametere(Parametere *param);

    QList<DataConnection*> connections() const;
    DataConnection *connection(QString connectionName);
    void addConnection(DataConnection *conn);
    void removeConnection(DataConnection *conn);

    void setDataSource(QString dataTableName, QSqlQuery &query);

    void print();

    PrintSettings *printSetting() const;
    void setPrintSetting(PrintSettings *printSetting);

private:
    ReportPrivate *d_ptr;
    Q_DECLARE_PRIVATE(Report)

    PrintSettings *_printSetting;

signals:
    void designerUpdateNeeded();

    friend class DocumentDesigner;
    friend class ReportModel;
};

LEAF_END_NAMESPACE

#endif // RREPORT_H

