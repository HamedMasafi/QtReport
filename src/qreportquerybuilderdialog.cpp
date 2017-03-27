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


#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <qreportdataconnection.h>

#include "qreportquerybuilderdialog.h"

#include "qreport.h"
#include "qreportdatatable.h"
#include "qreportparametere.h"

#define NODE_TYPE_TABLE_PARENT   0
#define NODE_TYPE_VIEW_PARENT    1
#define NODE_TYPE_TABLE          2
#define NODE_TYPE_VIEW           3

LEAF_BEGIN_NAMESPACE

LReportQueryBuilderDialog::LReportQueryBuilderDialog(LReport *report, QString connectionName, QWidget *parent) :
    QDialog(parent),
    _report(report)
{
    setupUi(this);

    LReportDataConnection *conn = report->connection(connectionName);

    qDebug() << connectionName;
    if (!conn) {
        QMessageBox msg;
        msg.setWindowTitle(tr("New datatable"));
        msg.setText(tr("Selected connection in not valid"));
        //msg.setDetailedText(db.lastError().text());
        msg.setIcon(QMessageBox::Warning);

        msg.exec();
        close();
        return;
    }//if

    db = QSqlDatabase::addDatabase(conn->driver());
    db.setHostName(conn->serverName());
    db.setDatabaseName(conn->databaseName());
    db.setUserName(conn->username());
    db.setPassword(conn->password());

    if (!db.open()) {
        QMessageBox msg;
        msg.setWindowTitle(tr("New datatable"));
        msg.setText(tr("Could open connect to database"));
        msg.setDetailedText(db.lastError().text());
        msg.setIcon(QMessageBox::Warning);

        msg.exec();
        close();
        return;
    }//if

    nodeTableDB = new QTreeWidgetItem(NODE_TYPE_TABLE_PARENT);
    nodeTableDB->setText(0, tr("Tables"));
    nodeTableDB->setIcon(0, QIcon(":/designer/table"));
    tablesTree->addTopLevelItem(nodeTableDB);

    nodeViewDB = new QTreeWidgetItem(NODE_TYPE_VIEW_PARENT);
    nodeViewDB->setText(0, tr("Views"));
    nodeViewDB->setIcon(0, QIcon(":/designer/form"));
    tablesTree->addTopLevelItem(nodeViewDB);

    QStringList tables = db.tables(QSql::Tables);
    QStringList views = db.tables(QSql::Views);

    for (int i = 0; i < tables.count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(NODE_TYPE_TABLE);
        item->setText(0, tables.at(i));
        nodeTableDB->addChild(item);
    }

    for (int i = 0; i < views.count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(NODE_TYPE_VIEW);
        item->setText(0, tables.at(i));
        nodeViewDB->addChild(item);
    }

}

QString LReportQueryBuilderDialog::tableName() const
{
    return _tableName;
}

void LReportQueryBuilderDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}

void LReportQueryBuilderDialog::on_tablesTree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem*)
{
    customQuery->setPlainText(QString("SELECT * FROM `%1`").arg(current->text(0)));
    _tableName = current->text(0);
}

QString LReportQueryBuilderDialog::query() const
{
    return customQuery->toPlainText();
}

LEAF_END_NAMESPACE
