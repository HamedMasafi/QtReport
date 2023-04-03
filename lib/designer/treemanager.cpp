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

#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QHeaderView>
#include <QCursor>
#include <QMessageBox>
#include <QMouseEvent>
#include <QMimeData>
#include <QDrag>

#include "treemanager.h"
#include "core/report.h"
#include "designer/documentdesigner.h"
#include "core/dataconnection.h"
#include "databaseinfodialog.h"
#include "parameteredialog.h"
#include "datatabledialog.h"
#include "core/parametere.h"
#include "core/reportmodel.h"

#define TYPE_CONNECTION "type_connection"
#define TYPE_DataTable "type_DataTable"
#define TYPE_PARAMETERE "type_parametere"
#define TYPE_FIELD "type_field"

LEAF_BEGIN_NAMESPACE

TreeManager::TreeManager(QWidget *parent, DocumentDesigner *designer, Report *report, bool readOnly) :
    QTreeWidget(parent),
    _designer(designer),
    _report(report),
    _readOnly(readOnly),
    nodeDataTable(0),
    nodeParameters(0)
{
    header()->setVisible(false);

    _contextMenu = new QMenu(this);

    initActions();
    initTreeItems();

    retranslateUi();
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(slot_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));

    connect(actionExpandAll,   SIGNAL(triggered()), this, SLOT(expandAll()));
    connect(actionCollapseAll, SIGNAL(triggered()), this, SLOT(collapseAll()));
    QMetaObject::connectSlotsByName(this);
}

void TreeManager::contextMenuEvent(QContextMenuEvent *event)
{
    _contextMenu->clear();

    _contextMenu->addAction(actionNewConnection);
    _contextMenu->addAction(actionNewParameter);


    if(currentItem()){
        QString data = currentItem()->data(1, 0).toString();
        //current item is connection node
        if(data == TYPE_CONNECTION){
            _contextMenu->addAction(actionNewDataTable);
            _contextMenu->addSeparator();
            _contextMenu->addAction(actionEditConnection);
            _contextMenu->addAction(actionDeleteConnection);
        }
        //current item is a parametere node
        if(data == TYPE_PARAMETERE){
            _contextMenu->addSeparator();
            _contextMenu->addAction(actionEditParameter);
            _contextMenu->addAction(actionDeleteParameter);
        }
        if(data == TYPE_DataTable){
            _contextMenu->addAction(actionNewDataTable);
            _contextMenu->addSeparator();
            _contextMenu->addAction(actionEditDataTable);
            _contextMenu->addAction(actionDeleteDataTable);
        }
    }

    _contextMenu->addSeparator();
    _contextMenu->addAction(actionExpandAll);
    _contextMenu->addAction(actionCollapseAll);

    _contextMenu->exec(event->globalPos());
}


void TreeManager::initActions()
{
    actionNewConnection= new QAction(this);
    actionNewConnection->setObjectName("actionNewConnection");
    actionNewConnection->setIcon(QIcon(":/designer/database-add"));

    actionEditConnection= new QAction(this);
    actionEditConnection->setObjectName("actionEditConnection");
    actionDeleteConnection= new QAction(this);
    actionDeleteConnection->setObjectName("actionDeleteConnection");
    actionDeleteConnection->setIcon(QIcon(":/designer/database-delete"));

    actionNewDataTable= new QAction(this);
    actionNewDataTable->setObjectName("actionNewDataTable");
    actionNewDataTable->setIcon(QIcon(":/designer/table-add"));

    actionEditDataTable= new QAction(this);
    actionEditDataTable->setObjectName("actionEditDataTable");
    actionDeleteDataTable= new QAction(this);
    actionDeleteDataTable->setObjectName("actionDeleteDataTable");

    actionNewParameter= new QAction(this);
    actionNewParameter->setObjectName("actionNewParameter");
    actionNewParameter->setIcon(QIcon(":/designer/form-add"));

    actionEditParameter= new QAction(this);
    actionEditParameter->setObjectName("actionEditParameter");
    actionDeleteParameter= new QAction(this);
    actionDeleteParameter->setObjectName("actionDeleteParameter");

    actionExpandAll = new QAction(this);
    actionExpandAll->setObjectName("actionExpandAll");
    actionExpandAll->setIcon(QIcon(":/designer/expand"));

    actionCollapseAll = new QAction(this);
    actionCollapseAll->setObjectName("actionCollapseAll");
    actionCollapseAll->setIcon(QIcon(":/designer/collapse"));

    _contextMenu->addAction(actionNewConnection);
    _contextMenu->addAction(actionNewDataTable);
    _contextMenu->addAction(actionNewParameter);
    _contextMenu->addSeparator();
    _contextMenu->addAction(actionExpandAll);
    _contextMenu->addAction(actionCollapseAll);
}

void TreeManager::slot_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem*)
{
    /*
    _contextMenu->clear();

    if(current == nodeDataTable){
        _contextMenu->addAction(actionNewConnection);
        _contextMenu->addAction(actionEditConnection);
        _contextMenu->addAction(actionDeleteConnection);
    }//if

    if(current == nodeParameters){
        _contextMenu->addAction(actionNewParameter);
        _contextMenu->addAction(actionEditParameter);
        _contextMenu->addAction(actionDeleteParameter);
    }//if
    */



}

void TreeManager::initToplevelItems()
{

}

void TreeManager::changeEvent(QEvent *e)
{
    QTreeWidget::changeEvent(e);

    if(e->type() == QEvent::LanguageChange)
        retranslateUi();
}

void TreeManager::retranslateUi()
{
    nodeDataTable->setText(0, tr("Data source"));
    nodeParameters->setText(0, tr("Parameters"));

    actionNewConnection->setText(tr("New connecion"));
    actionEditConnection->setText(tr("Edit connecion"));
    actionDeleteConnection->setText(tr("Delete connecion"));

    actionNewDataTable->setText(tr("New data table"));
    actionEditDataTable->setText(tr("Edit data table"));
    actionDeleteDataTable->setText(tr("Delete data table"));

    actionNewParameter->setText(tr("New parameter"));
    actionEditParameter->setText(tr("Edit parameter"));
    actionDeleteParameter->setText(tr("Delete parameter"));

    actionExpandAll->setText(tr("Expand all"));
    actionCollapseAll->setText(tr("Collapse all"));

    _contextMenu->setTitle(tr("Report directory"));
}

QMenu *TreeManager::createContextMenu()
{
    if(!_contextMenu)
        _contextMenu = new QMenu(this);

    return _contextMenu;
}


void TreeManager::on_actionNewConnection_triggered()
{
    DataConnection *conn = _designer->addDataConnection();
    if(conn)
        addConnectionNode(conn);

//    DatabaseInfoDialog info(_report);

//    if(info.exec() != QDialog::Accepted) return;

//    DataConnection *conn = info.dataConnection();

//    _report->addConnection(conn);
}

void TreeManager::on_actionEditConnection_triggered()
{
    DataConnection *conn = _designer->editDataConnection(currentItem()->data(2, 0).toString());

    if(conn){
        setItemText(conn->objectName());
        setItemName(conn->objectName());
    }//if
}

void TreeManager::on_actionDeleteConnection_triggered()
{
    bool b = _designer->removeDataConnection(currentItem()->data(2, 0).toString());

    if(b)
        nodeDataTable->removeChild(currentItem());
}

void TreeManager::on_actionNewParameter_triggered()
{
    Parametere *p = _designer->addParametere();
    if(p)
        addParametereNode(p);
}

void TreeManager::on_actionEditParameter_triggered()
{
    Parametere *p = _designer->editParametere(itemName());
    if(p){
        setItemText(p->objectName());
        setItemName(p->objectName());
    }//if
}

void TreeManager::on_actionDeleteParameter_triggered()
{
    bool b = _designer->removeParametere(itemName());

    if(b)
        nodeParameters->removeChild(currentItem());
}

void TreeManager::on_actionNewDataTable_triggered()
{
    DataTable *table = _designer->addDataTable(itemName());

    if(table)
        initTreeItems();

//    DataTableDialog dialog(_report, itemName());

//    if(dialog.exec() == QDialog::Accepted){
//        DataTable *table = dialog.createDataTable();
//        _report->addDataTable(table);

//        /*
//        QTreeWidgetItem *newTableItem = new QTreeWidgetItem;
//        newTableItem->setData(1, 0, TYPE_DataTable);
//        newTableItem->setText(0, table->objectName());
//        newTableItem->setIcon(0, QIcon(":/designer/table"));
//        currentItem()->addChild(newTableItem);

//        for(int i = 0; i < table->fields().count(); i++) {
//            QTreeWidgetItem *newFieldItem = new QTreeWidgetItem;
//            newFieldItem->setData(1, 0, TYPE_FIELD);
//            newFieldItem->setData(2, 0, table->fields().at(i)->type());
//            newFieldItem->setText(0, table->fields().at(i)->objectName());
//            newFieldItem->setIcon(0, QIcon(":/designer/field"));
//            newTableItem->addChild(newFieldItem);
//        }//for

//        newTableItem->setExpanded(true);
//        currentItem()->setExpanded(true);
//        */
//    }//if
}

void TreeManager::on_actionEditDataTable_triggered()
{
    DataTable *table = _designer->editDataTable(itemName());

    if(table)
        initTreeItems();
}

void TreeManager::on_actionDeleteDataTable_triggered()
{
    bool b = _designer->removeDataTable(itemName());

    if(b)
        initTreeItems();
}


void TreeManager::initTreeItems()
{
    bool isDatatableOpen = nodeDataTable && nodeDataTable->isExpanded();
    bool isParameteresOpen = nodeParameters && nodeParameters->isExpanded();

    clear();

    nodeDataTable = new QTreeWidgetItem;
    nodeDataTable->setIcon(0, QIcon(":/designer/database"));
    nodeDataTable->setData(0, 0, "DataTable");
    addTopLevelItem(nodeDataTable);

    nodeParameters = new QTreeWidgetItem;
    nodeParameters->setIcon(0, QIcon(":/designer/form"));
    nodeParameters->setData(0, 0, "params");
    addTopLevelItem(nodeParameters);

    /*for(int i = 0; i < nodeDataTable->childCount(); i++)
        nodeDataTable->removeChild(nodeDataTable->child(i));

    for(int i = 0; i < nodeParameters->childCount(); i++)
        nodeParameters->removeChild(nodeParameters->child(i));*/

    for(int i = 0; i < _report->parameters().count(); i++)
        addParametereNode(_report->parameters().at(i));

    for(int i = 0; i < _report->connections().count(); i++){
        QTreeWidgetItem *newConnectionItem = addConnectionNode(_report->connections().at(i));

        QList<DataTable*> DataTables = _report->dataTablesByConnections(_report->connections().at(i)->objectName());

        //add DataTables if current connection
        foreach (DataTable *dataTable, DataTables) {
            QTreeWidgetItem *newTableItem = addTableNode(newConnectionItem, dataTable);

            for(int k = 0; k < dataTable->fields().count(); k++)
                addFieldNode(newTableItem, dataTable->fields().at(k));
        }
    }//for

    if(isDatatableOpen)
        nodeDataTable->setExpanded(true);
    if(isParameteresOpen)
        nodeParameters->setExpanded(true);
    retranslateUi();
}

QTreeWidgetItem *TreeManager::addConnectionNode(DataConnection *connection)
{
    QTreeWidgetItem *newConnItem = new QTreeWidgetItem;
    newConnItem->setData(1, 0, TYPE_CONNECTION);
    newConnItem->setData(2, 0, connection->objectName());
    newConnItem->setText(0, connection->objectName());
    nodeDataTable->addChild(newConnItem);

    return newConnItem;
}

QTreeWidgetItem *TreeManager::addTableNode(QTreeWidgetItem *connectionItem, DataTable *table)
{
    QTreeWidgetItem *newTableItem = new QTreeWidgetItem;

    setItemType(TYPE_DataTable, newTableItem);
    setItemName(table->objectName(), newTableItem);
    setItemText(table->objectName(), newTableItem);
    newTableItem->setData(3, 0, table->connectionName());
    newTableItem->setIcon(0, QIcon(":/designer/table"));
    connectionItem->addChild(newTableItem);

    return newTableItem;
}

QTreeWidgetItem *TreeManager::addFieldNode(QTreeWidgetItem *DataTableItem, DataField *field)
{
    QTreeWidgetItem *newFieldItem = new QTreeWidgetItem;
    newFieldItem->setData(1, 0, TYPE_FIELD);
    newFieldItem->setData(2, 0, field->objectName());
    newFieldItem->setText(0, field->objectName());
    newFieldItem->setIcon(0, QIcon(":/designer/field"));
    DataTableItem->addChild(newFieldItem);

    return newFieldItem;
}

QTreeWidgetItem *TreeManager::addParametereNode(Parametere *parametere)
{
    QTreeWidgetItem *newParamItem = new QTreeWidgetItem;
    newParamItem->setData(1, 0, TYPE_PARAMETERE);
    newParamItem->setData(2, 0, parametere->objectName());
    newParamItem->setText(0, parametere->objectName());
    nodeParameters->addChild(newParamItem);

    return newParamItem;
}

QString TreeManager::itemText()
{
    return currentItem()->text(0);
}

void TreeManager::setItemText(QString caption)
{
    setItemText(caption, currentItem());
}

void TreeManager::setItemText(QString caption, QTreeWidgetItem *item)
{
    item->setText(0, caption);
}

QString TreeManager::itemName()
{
    return currentItem()->data(2, 0).toString();
}

void TreeManager::setItemName(QString name)
{
    setItemName(name, currentItem());
}

void TreeManager::setItemName(QString name, QTreeWidgetItem *item)
{
    item->setData(2, 0, name);
}

QString TreeManager::itemType()
{
    return currentItem()->data(1, 0).toString();
}

void TreeManager::setItemType(QString type)
{
    setItemType(type, currentItem());
}

void TreeManager::setItemType(QString type, QTreeWidgetItem *item)
{
    item->setData(1, 0, type);
}

void TreeManager::mousePressEvent(QMouseEvent *event)
{
    // Get current selection
    QTreeWidgetItem *selectedItem = currentItem();

    // If the selected Item exists
    if (event->button() == Qt::LeftButton && selectedItem)
        if(selectedItem->data(1, 0) == TYPE_FIELD)
        {

            // Create data
            QMimeData *mimeData = new QMimeData();
            mimeData->setText(tr("Report textbox"));
            mimeData->setData("text", QVariant(selectedItem->text(0)).toByteArray());

            // Create drag
            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            drag->exec(Qt::CopyAction);
        }

    QTreeWidget::mousePressEvent(event);
}

LEAF_END_NAMESPACE
