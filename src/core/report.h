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

class LReportParametere;
class LReportPrivate;
class LReportWidgetBase;
class LReportBand;
class LReportDataConnection;
class LReportPrintSettings;
class LEAF_EXPORT LReport : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath USER true)

public:

    enum XmlNodeType{
        Widget      = 1,
        Band        = 2,
        Connection  = 4,
        DataTable   = 8,
        Parametere  = 16,
        All         = Widget | Band | Connection | DataTable | Parametere
    };

    LReport();

    bool load(QString path);
    void save(QString path = "");

    QByteArray getXmlContent(int NodeFlags = All) const;


    QList<LReportBand*>          *bands();
    QList<LReportWidgetBase*>    *widgets();

    // designer
    void removeBand(QString name);
    void removeWidget(QString name);

    void widgetToBack(LReportWidgetBase*);
    void widgetToFront(LReportWidgetBase*);
    void bandToBack(LReportBand*);
    void bandToFront(LReportBand*);

    void changeParent(LReportWidgetBase*, LReportBand*);

    // print
    void setParametereValue(QString name, QVariant value);

    QString filePath() const;



    //todo: return one object
    QList<LReportDataTable*> dataTablesByName(QString tableName);
    QList<LReportDataTable*> dataTablesByConnections(QString connectionName);
    QList<LReportDataTable*> dataTables();

    void addDataTable(LReportDataTable *dataTable);
    LReportDataTable *dataTable(QString tableName);
    LReportDataTable *dataTable(QString tableName, QString connectionName);
    void removeDataTable(LReportDataTable *table);

    LReportBand *section(QString sectionName);
    LReportBand *findBandByName(QString bandName);
    LReportDataConnection *findConnectionByName(QString connectionName);
    LReportWidgetBase *findWidgetByName(QString widgetName);

    LReportParametere *parameter(QString name);
    QList<LReportParametere*> parameters();
    void addParametere(QString name, QVariant value);
    void addParametere(LReportParametere *param);
    void removeParametere(LReportParametere *param);

    QList<LReportDataConnection*> connections() const;
    LReportDataConnection *connection(QString connectionName);
    void addConnection(LReportDataConnection *conn);
    void removeConnection(LReportDataConnection *conn);

    void setDataSource(QString dataTableName, QSqlQuery &query);

    void print();

    LReportPrintSettings *printSetting() const;
    void setPrintSetting(LReportPrintSettings *printSetting);

private:
    LReportPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(LReport)

    LReportPrintSettings *_printSetting;

signals:
    void designerUpdateNeeded();

    friend class LReportDocumentDesigner;
};

LEAF_END_NAMESPACE

#endif // RREPORT_H

