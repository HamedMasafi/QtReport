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

#include <QList>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>

#include "core/report.h"
#include "databasetablesdialog.h"
#include "core/dataconnection.h"
#include "core/datatable.h"
#include "core/parametere.h"

#define NODE_TYPE_TABLE_PARENT 0
#define NODE_TYPE_VIEW_PARENT 1
#define NODE_TYPE_TABLE 2
#define NODE_TYPE_VIEW 3

LEAF_BEGIN_NAMESPACE

DatabaseTablesDialog::DatabaseTablesDialog(Report *report, QString connectionName, QWidget *parent)
    : QDialog(parent), _report(report)
{
    setupUi(this);

    DataConnection *conn = _report->connection(connectionName);

    db = QSqlDatabase::addDatabase(conn->driver());
    db.setHostName(conn->serverName());
    db.setDatabaseName(conn->databaseName());
    db.setUserName(conn->username());
    db.setPassword(conn->password());

    if (!db.open()) {
        QMessageBox msg;
        msg.setWindowTitle(tr("New datatable"));
        msg.setText(tr("Could not connect to database"));
        msg.setDetailedText(db.lastError().text());
        msg.setIcon(QMessageBox::Warning);

        close();
    } //if

    nodeTableDB = new QTreeWidgetItem(NODE_TYPE_TABLE_PARENT);
    nodeTableDB->setText(0, tr("Tables"));
    treeWidget->addTopLevelItem(nodeTableDB);

    nodeViewDB = new QTreeWidgetItem(NODE_TYPE_VIEW_PARENT);
    nodeViewDB->setText(0, tr("Views"));
    treeWidget->addTopLevelItem(nodeViewDB);

    nodeTableReport = new QTreeWidgetItem(NODE_TYPE_TABLE_PARENT);
    nodeTableReport->setText(0, tr("Tables"));
    treeWidgetReportScheema->addTopLevelItem(nodeTableReport);

    nodeViewReport = new QTreeWidgetItem(NODE_TYPE_VIEW_PARENT);
    nodeViewReport->setText(0, tr("Views"));
    treeWidgetReportScheema->addTopLevelItem(nodeViewReport);

    QStringList tables = db.tables(QSql::Tables);
    QStringList views = db.tables(QSql::Views);

    for (int i = 0; i < tables.count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(NODE_TYPE_TABLE);
        item->setText(0, tables.at(i));
        nodeTableDB->addChild(item);

        QListWidgetItem *listItem = new QListWidgetItem(tables.at(i));
        listItem->setCheckState(Qt::Unchecked);
        listWidgetTables->addItem(listItem);
    }

    for (int i = 0; i < views.count(); i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(NODE_TYPE_VIEW);
        item->setText(0, tables.at(i));
        nodeViewDB->addChild(item);

        QListWidgetItem *listItem = new QListWidgetItem(tables.at(i));
        listItem->setCheckState(Qt::Unchecked);
        listWidgetViews->addItem(listItem);
    }

    for (int i = 0; i < _report->parameters().count(); i++)
        listWidgetParameters->addItem(_report->parameters().at(i)->objectName());
}

void DatabaseTablesDialog::changeEvent(QEvent *e)
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

void DatabaseTablesDialog::on_buttonBox_accepted()
{
    for (int i = 0; i < listWidgetTables->count(); i++)
        if (listWidgetTables->item(i)->checkState() == Qt::Checked) {
            /*DataTable *table = new DataTable;

         table->setName( listWidgetTables->item( i )->text() );
         QSqlRecord record = db.record( listWidgetTables->item(i)->text() );

         table->appendRecordFields( &record );

         //_report->tables().append( &table );
         _report->appendTables( table );*/
        } //if
}

void DatabaseTablesDialog::on_toolButtonAdd_clicked()
{
    QTreeWidgetItem *item = treeWidget->currentItem();

    if (item->type() == NODE_TYPE_TABLE)
        if (treeWidgetReportScheema->findItems(item->text(0), Qt::MatchExactly).count() == 0) {
            QTreeWidgetItem *newItem = new QTreeWidgetItem(NODE_TYPE_TABLE);
            newItem->setText(0, item->text(0));
            nodeTableReport->addChild(newItem);
        }
    //item->type()
}

void DatabaseTablesDialog::on_listWidgetTables_currentItemChanged(QListWidgetItem *current,
                                                                  QListWidgetItem *)
{
    textEditCustomQuery->setText(QString("select  *from %1").arg(current->text()));
}

void DatabaseTablesDialog::on_listWidgetParameters_itemDoubleClicked(QListWidgetItem *item)
{
    textEditCustomQuery->insertPlainText(QString("{%1}").arg(item->text()));
}

LEAF_END_NAMESPACE
