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

#ifndef QREPORTDATATABLEDIALOG_H
#define QREPORTDATATABLEDIALOG_H

#include "qtreportglobal.h"
#include "ui_qreportdatatabledialog.h"

LEAF_BEGIN_NAMESPACE

class QReport;
class QReportDataTable;
class Q_DECL_HIDDEN QReportDataTableDialog : public QDialog, private Ui::QReportDataTableDialog
{
    Q_OBJECT
    QReportDataTable *_table;
    QReport *_report;
    QString _connectionName;
    bool _editMode;

    void fetchScheema();
    bool checkData();

public:
    explicit QReportDataTableDialog(QReport *report, QString connectionName, QWidget *parent = 0);
    explicit QReportDataTableDialog(QReport *report, QReportDataTable *table, QWidget *parent = 0);

    QReportDataTable *createDataTable();

    void fillIntOperatorCombo();
    void fillStringOperatorCombo();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_queryBuilderButton_clicked();
    void on_buttonBox_accepted();
    void on_treeWidgetFields_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void setFilterText();
};

LEAF_END_NAMESPACE

#endif // QREPORTDATATABLEDIALOG_H
