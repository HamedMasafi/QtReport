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

#include "qtreportglobal.h"
#include <QTreeWidget>

class QMenu;
class QAction;

LEAF_BEGIN_NAMESPACE

class Report;
class DataTable;
class DataField;
class Parametere;
class DataConnection;
class DocumentDesigner;
enum TreeNodeTypeFlag
{
   DataTableType,
   ParametersType,
   VariblesType
};
Q_DECLARE_FLAGS(TreeNodeType, TreeNodeTypeFlag)
Q_DECLARE_OPERATORS_FOR_FLAGS(TreeNodeType)


class TreeManager : public QTreeWidget
{
    Q_OBJECT


public:
    TreeManager(QWidget *parent = 0, DocumentDesigner *designer = 0, Report *report = 0, bool readOnly = false);

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

    QTreeWidgetItem *addConnectionNode(DataConnection *);
    QTreeWidgetItem *addTableNode(QTreeWidgetItem *, DataTable *);
    QTreeWidgetItem *addFieldNode(QTreeWidgetItem *, DataField *);
    QTreeWidgetItem *addParametereNode(Parametere *);

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
    Report  *_report;
    bool _readOnly;
    DocumentDesigner *_designer;

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

LEAF_END_NAMESPACE

#endif // QREPORTTREEMANAGER_H
