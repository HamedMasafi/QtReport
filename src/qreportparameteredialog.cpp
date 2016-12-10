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

#include <QValidator>
#include <QRegExp>
#include <QMessageBox>
#include <qreportparametere.h>

#include "qreportparameteredialog.h"
#include "qreporttypehelper.h"
#include "qreportparametere.h"
#include "qreport.h"

class QReportParametereDialogPrivate{
    QReport *report;
    QReportParametere *paremetere;

    QReportParametereDialog *q_ptr;
    Q_DECLARE_PUBLIC(QReportParametereDialog)

public:
    QReportParametereDialogPrivate(QReportParametereDialog *parent) : q_ptr(parent){

    }
};

QReportParametereDialog::QReportParametereDialog(QReport *report, QReportParametere *param) :
    QDialog(),
    d_ptr(new QReportParametereDialogPrivate(this))
{
    setupUi(this);

    Q_D(QReportParametereDialog);

    d->report = report;
    d->paremetere = param;

    if(param){
        lineEditName->setText(param->objectName());
        lineEditDefValue->setText(param->defaultValue().toString());
        comboBoxType->setCurrentIndex(comboBoxType->findText(QReportTypeHelper::typeToString((QVariant::Type)param->type())));

        setWindowTitle(tr("Edit parametere"));
    } else {
        setWindowTitle(tr("Add new parametere"));
    }

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    lineEditName->setValidator(validator);
}

QReportParametere *QReportParametereDialog::parametere() const
{
    Q_D(const QReportParametereDialog);
    return d->paremetere;
}

void QReportParametereDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
       case QEvent::LanguageChange:
           retranslateUi(this);
           break;

       default:
           break;
    }
}


void QReportParametereDialog::on_buttonBox_accepted()
{
    Q_D(QReportParametereDialog);

    if(lineEditName->text().isEmpty()){
        QMessageBox::warning(this,
                                 windowTitle(),
                                 tr("Enter parametere name."),
                                 QMessageBox::Ok);
        return;
    }

    QReportParametere *p = d->report->parameter(lineEditName->text());
    if(p && p != d->paremetere) {
        QMessageBox::information(this,
                                 windowTitle(),
                                 tr("A parametere with same name alerty exists."),
                                 QMessageBox::Ok);
    } else {
        if(!d->paremetere)
            d->paremetere = new QReportParametere();

        d->paremetere->setObjectName(lineEditName->text());
        d->paremetere->setDefaultValue(lineEditDefValue->text());
        d->paremetere->setType(QReportTypeHelper::stringToType(comboBoxType->currentText()));

        accept();
    }
}
