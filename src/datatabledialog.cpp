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

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtGui/QRegExpValidator>
#include <QtCore/QRegExp>
#include <QMessageBox>
#include <QDomElement>
#include <QDebug>

#include "report.h"
#include "typehelper.h"
#include "datatable.h"
#include "parametere.h"
#include "datatabledialog.h"
#include "querybuilderdialog.h"

LEAF_BEGIN_NAMESPACE

LReportDataTableDialog::LReportDataTableDialog(LReport *report, QString connectionName, QWidget *parent) :
    QDialog(parent),
    _report(report),
    _table(0),
    _connectionName(connectionName),
    _editMode(false)
{
    setupUi(this);

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    datasourceName->setValidator(validator);

    for(int i = 0; i < _report->parameters().count(); i++)
        comboBoxParameter->addItem(_report->parameters().at(i)->objectName());

    fillIntOperatorCombo();

}

LReportDataTableDialog::LReportDataTableDialog(LReport *report, LReportDataTable *table, QWidget *parent) :
    QDialog(parent),
    _report(report),
    _table(table),
    _connectionName(""),
    _editMode(true)
{
    setupUi(this);

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    datasourceName->setValidator(validator);

    if(table)
        setWindowTitle(tr("Add new data table"));
    else
        setWindowTitle(tr("Edit data table"));

    datasourceName->setText(table->objectName());
    querySql->setPlainText(table->selectCommand());
    foreach (LReportDataField *field, table->fields()) {
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, field->objectName());
        item->setText(1, LReportTypeHelper::typeToString((QVariant::Type)field->type()));
        treeWidgetFields->addTopLevelItem(item);
    }

    for(int i = 0; i < _report->parameters().count(); i++)
        comboBoxParameter->addItem(_report->parameters().at(i)->objectName());

    fillIntOperatorCombo();
}

void LReportDataTableDialog::changeEvent(QEvent *e)
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


void LReportDataTableDialog::on_queryBuilderButton_clicked()
{
    QString cn = _table ? _table->connectionName() : _connectionName;

    LReportQueryBuilderDialog dialog(_report, cn, this);
    if(dialog.exec() == QDialog::Accepted) {
        datasourceName->setText(dialog.tableName());
        querySql->setPlainText(dialog.query());
        fetchScheema();
    }//if
}

void LReportDataTableDialog::fetchScheema()
{
    QSqlQuery q(querySql->toPlainText());
    QSqlRecord records = q.record();

    treeWidgetFields->clear();
    for(int i = 0; i < records.count(); i++){
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0, records.fieldName(i));
        item->setText(1, LReportTypeHelper::typeToString(records.field(i).type()));
        treeWidgetFields->addTopLevelItem(item);
    }//for
}


LReportDataTable *LReportDataTableDialog::createDataTable()
{
    if(!_table)
        _table = new LReportDataTable(_connectionName);
    else
        _table->clear();

    _table->setObjectName(datasourceName->text());
    _table->setSelectCommand(querySql->toPlainText());

    for(int i = 0;  i < treeWidgetFields->topLevelItemCount(); i++){
        QTreeWidgetItem *item = treeWidgetFields->topLevelItem(i);
        LReportDataField *field = new LReportDataField(item->text(0));
        field->setType((LReportTypeHelper::stringToType(item->text(1))));
        field->setFilter(item->text(2));
        _table->append(field);
    }

    return _table;
}

bool LReportDataTableDialog::checkData()
{
    if(datasourceName->text().trimmed() == ""){
        QMessageBox::warning(this,
                             windowTitle(),
                             tr("Please enter datasource name."),
                             QMessageBox::Ok);
        return false;
    }//if

    bool exists = false;
    if(_editMode){
        if(datasourceName->text() != _table->objectName() && _report->dataTable(datasourceName->text()))
            exists = true;
    }else if(_report->dataTable(datasourceName->text())){
        exists = true;
    }

    if(exists){
        QMessageBox::warning(this,
                             windowTitle(),
                             tr("A datasource with same name alerty exists."),
                             QMessageBox::Ok);
        return false;
    }//if

    return true;
}

void LReportDataTableDialog::on_buttonBox_accepted()
{
    if(checkData())
        this->accept();
}

void LReportDataTableDialog::on_treeWidgetFields_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    QString type = current->text(1).toLower();
    QString filter = current->text(2);

    groupBoxFilter->setChecked(!filter.isEmpty());

    if(!filter.contains(" ")){
        lineEditFilterValue->clear();
        comboBoxOperator->setCurrentIndex(0);
        comboBoxParameter->setCurrentIndex(0);
        return;
    }

    QStringList sp = filter.split(" ");

    QString op = sp.at(0);
    QString data = sp.at(1);
    data = data.replace("'", "").replace("{", "").replace("}", "");

    comboBoxOperator->clear();

    if(type == "int" || type == "double"){
        fillIntOperatorCombo();
    }else if (type == "string" || type == "char"){
        fillStringOperatorCombo();
    }
    if(filter.isEmpty()){
        lineEditFilterValue->clear();
    }else if(filter.contains("{")){
        comboBoxOperator->setCurrentIndex(comboBoxOperator->findData(op));
        comboBoxParameter->setCurrentIndex(comboBoxParameter->findText(data));
        radioFilterParametere->setChecked(true);
    }else if(filter != ""){
        comboBoxOperator->setCurrentIndex(comboBoxOperator->findData(op));
        lineEditFilterValue->setText(data);
        radioFilterValue->setChecked(true);
    }


}


void LReportDataTableDialog::fillIntOperatorCombo()
{
    comboBoxOperator->addItem("Equal", "=");
    comboBoxOperator->addItem("Less than", "<");
    comboBoxOperator->addItem("Less than or equal", "<=");
    comboBoxOperator->addItem("Greater than", ">");
    comboBoxOperator->addItem("greater than or equal", ">=");
    comboBoxOperator->addItem("Not equal", "!=");
}

void LReportDataTableDialog::fillStringOperatorCombo()
{
    comboBoxOperator->addItem("Equal", "=");
    comboBoxOperator->addItem("Like", "LIKE");
}

void LReportDataTableDialog::setFilterText()
{
    if(!treeWidgetFields->currentItem())
        return;

    QString t = "";
    if(groupBoxFilter->isChecked()){
        t = comboBoxOperator->itemData(comboBoxOperator->currentIndex()).toString();
        treeWidgetFields->currentItem()->setData(2, QTreeWidgetItem::UserType, t);
        t.append(" '");

        if(radioFilterValue->isChecked()){
            t.append(lineEditFilterValue->text());
            treeWidgetFields->currentItem()->setData(3, QTreeWidgetItem::UserType, lineEditFilterValue->text());
        }

        if(radioFilterParametere->isChecked()){
            t.append("{" + comboBoxParameter->currentText() + "}");
            treeWidgetFields->currentItem()->setData(3, QTreeWidgetItem::UserType, comboBoxParameter->currentText());
        }

        t.append("'");
    }
    treeWidgetFields->currentItem()->setText(2, t);
}

LEAF_END_NAMESPACE
