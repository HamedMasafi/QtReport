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


#ifndef RDATABASETABLESDIALOG_H
#define RDATABASETABLESDIALOG_H

#include "qtreportglobal.h"
#include "ui_databasetablesdialog.h"

#include <QSqlDatabase>

class QTreeWidgetItem;

LEAF_BEGIN_NAMESPACE

class LReport;

class LReportDatabaseTablesDialog : public QDialog, private Ui::LReportDatabaseTablesDialog
{
    Q_OBJECT

public:
    LReportDatabaseTablesDialog(LReport *report, QString connectionName, QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);

private:
    LReport *_report;
    QTreeWidgetItem *nodeTableDB;
    QTreeWidgetItem *nodeViewDB;
    QTreeWidgetItem *nodeTableReport;
    QTreeWidgetItem *nodeViewReport;
    QSqlDatabase db;

private slots:
    void on_toolButtonAdd_clicked();
    void on_buttonBox_accepted();
    void on_listWidgetTables_currentItemChanged(QListWidgetItem *current, QListWidgetItem*);
    void on_listWidgetParameters_itemDoubleClicked(QListWidgetItem *item);
};

LEAF_END_NAMESPACE

#endif // RDATABASETABLESDIALOG_H
