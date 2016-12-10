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

#ifndef QREPORTTREEMANAGER_H
#define QREPORTTREEMANAGER_H

#include <QTreeWidget>

class QReport;
class QMenu;
class QAction;
class QReportDataTable;
class QReportDataField;
class QReportParametere;
class QReportDataConnection;
class QReportDocumentDesigner;
enum TreeNodeTypeFlag
{
   DataTable,
   Parameters,
   Varibles
};
Q_DECLARE_FLAGS(TreeNodeType, TreeNodeTypeFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(TreeNodeType)


class QReportTreeManager : public QTreeWidget
{
    Q_OBJECT


public:
    QReportTreeManager(QWidget *parent = 0, QReportDocumentDesigner *designer = 0, QReport *report = 0, bool readOnly = false);

    QMenu *createContextMenu();

public slots:
    void slot_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_actionNewConnection_triggered();
    void on_actionEditConnection_triggered();
    void on_actionDeleteConnection_triggered();

    void on_actionNewDataTable_triggered();
    void on_actionEditDataTable_triggered();
    void on_actionDeleteDataTable_triggered();

    void on_actionNewParameter_triggered();
    void on_actionEditParameter_triggered();
    void on_actionDeleteParameter_triggered();

    void initTreeItems();

protected:
    void changeEvent(QEvent *e);
    void retranslateUi();
    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void initToplevelItems();
    void initActions();

    QTreeWidgetItem *addConnectionNode(QReportDataConnection *);
    QTreeWidgetItem *addTableNode(QTreeWidgetItem *, QReportDataTable *);
    QTreeWidgetItem *addFieldNode(QTreeWidgetItem *, QReportDataField *);
    QTreeWidgetItem *addParametereNode(QReportParametere *);

    QMenu *_contextMenu;

    QAction *actionNewConnection;
    QAction *actionEditConnection;
    QAction *actionDeleteConnection;

    QAction *actionNewDataTable;
    QAction *actionEditDataTable;
    QAction *actionDeleteDataTable;

    QAction *actionNewParameter;
    QAction *actionEditParameter;
    QAction *actionDeleteParameter;

    QAction *actionExpandAll;
    QAction *actionCollapseAll;

    QTreeWidgetItem *nodeDataTable;
    QTreeWidgetItem *nodeParameters;
    QReport  *_report;
    bool _readOnly;
    QReportDocumentDesigner *_designer;

    QString itemText();
    void setItemText(QString caption);
    void setItemText(QString caption, QTreeWidgetItem *item);

    QString itemName();
    void setItemName(QString name);
    void setItemName(QString name, QTreeWidgetItem *item);

    QString itemType();
    void setItemType(QString type);
    void setItemType(QString type, QTreeWidgetItem *item);
};

#endif // QREPORTTREEMANAGER_H
