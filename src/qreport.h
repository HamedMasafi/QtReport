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

#include "qtreportglobal.h"
#include "qreportdatatable.h"

template <typename T> class QList;
template <class Key, class T> class QHash;
class QSizeF;
class QSizeF;
class QVariant;
class QString;

LEAF_BEGIN_NAMESPACE

class QReportParametere;
class QReportPrivate;
class QReportWidgetBase;
class QReportBand;
class QReportDataConnection;
class LEAF_EXPORT QReport : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal marginTop     READ marginTop    WRITE setMarginTop    USER true)
    Q_PROPERTY(qreal marginBottom  READ marginBottom WRITE setMarginBottom USER true)
    Q_PROPERTY(qreal marginLeft    READ marginLeft   WRITE setmarginLeft   USER true)
    Q_PROPERTY(qreal marginRight   READ marginRight  WRITE setMarginRight  USER true)

    Q_PROPERTY(QString filePath      READ filePath     USER true)

public:

    enum XmlNodeType{
        Widget      = 1,
        Band        = 2,
        Connection  = 4,
        DataTable   = 8,
        Parametere  = 16,
        All         = Widget | Band | Connection | DataTable | Parametere
    };

    QReport();

    bool load(QString path);
    void save(QString path = "");
    QByteArray getXmlContent(int NodeFlags = All) const;

    QList<QReportBand*>          *bands();
    QList<QReportWidgetBase*>    *widgets();

    void removeBand(QString name);
    void removeWidget(QString name);

    void setParameterValue(QString, QVariant);
    void setMargins(qreal _marginLeft, qreal _marginTop,
                    qreal _marginRight, qreal _marginBottom);

    qreal marginLeft() const;
    qreal marginBottom() const;
    qreal marginTop() const;
    qreal marginRight() const;

    void setmarginLeft(qreal value);
    void setMarginRight(qreal value);
    void setMarginTop(qreal value);
    void setMarginBottom(qreal value);

    QSizeF designArea() const;
    QSizeF pageSize() const;
    void setSize(QSizeF s);
    void setSize(qreal width, qreal height);
    void setWidth(qreal width);
    void setHight(qreal height);

    QString filePath() const;

    void widgetToBack(QReportWidgetBase*);
    void widgetToFront(QReportWidgetBase*);
    void bandToBack(QReportBand*);
    void bandToFront(QReportBand*);

    void changeParent(QReportWidgetBase*, QReportBand*);

    QList<QReportDataTable*> dataTablesByName(QString tableName);
    QList<QReportDataTable*> dataTablesByConnections(QString connectionName);
    QList<QReportDataTable*> dataTables();
    void addDataTable(QReportDataTable *dataTable);
    QReportDataTable *dataTable(QString tableName);
    QReportDataTable *dataTable(QString tableName, QString connectionName);
    void removeDataTable(QReportDataTable *table);

    QReportBand *section(QString sectionName);
    QReportBand *findBandByName(QString bandName);
    QReportDataConnection *findConnectionByName(QString connectionName);
    QReportWidgetBase *findWidgetByName(QString widgetName);

    QReportParametere *parameter(QString name);
    QList<QReportParametere*> parameters();
    void addParametere(QString name, QVariant value);
    void addParametere(QReportParametere *param);
    void setParametereValue(QString name, QVariant value);
    void removeParametere(QReportParametere *param);

    QList<QReportDataConnection*> connections() const;
    QReportDataConnection *connection(QString connectionName);
    void addConnection(QReportDataConnection *conn);
    void removeConnection(QReportDataConnection *conn);

private:
    QReportPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(QReport)


signals:
    void designerUpdateNeeded();

    friend class QReportDocumentDesigner;
};

LEAF_END_NAMESPACE

#endif // RREPORT_H

