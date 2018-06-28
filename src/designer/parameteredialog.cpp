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

#include "parameteredialog.h"
#include "typehelper.h"
#include "parametere.h"
#include "core/report.h"
#include "parametere.h"

LEAF_BEGIN_NAMESPACE

class ParametereDialogPrivate{
    Report *report;
    Parametere *paremetere;

    ParametereDialog *q_ptr;
    Q_DECLARE_PUBLIC(ParametereDialog)

public:
    ParametereDialogPrivate(ParametereDialog *parent) : q_ptr(parent){

    }
};

ParametereDialog::ParametereDialog(Report *report, Parametere *param) :
    QDialog(),
    d_ptr(new ParametereDialogPrivate(this))
{
    setupUi(this);

    Q_D(ParametereDialog);

    d->report = report;
    d->paremetere = param;

    if(param){
        lineEditName->setText(param->objectName());
        lineEditDefValue->setText(param->defaultValue().toString());
        comboBoxType->setCurrentIndex(comboBoxType->findText(TypeHelper::typeToString((QVariant::Type)param->type())));

        setWindowTitle(tr("Edit parametere"));
    } else {
        setWindowTitle(tr("Add new parametere"));
    }

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    lineEditName->setValidator(validator);
}

Parametere *ParametereDialog::parametere() const
{
    Q_D(const ParametereDialog);
    return d->paremetere;
}

void ParametereDialog::changeEvent(QEvent *e)
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


void ParametereDialog::on_buttonBox_accepted()
{
    Q_D(ParametereDialog);

    if(lineEditName->text().isEmpty()){
        QMessageBox::warning(this,
                                 windowTitle(),
                                 tr("Enter parametere name."),
                                 QMessageBox::Ok);
        return;
    }

    Parametere *p = d->report->parameter(lineEditName->text());
    if(p && p != d->paremetere) {
        QMessageBox::information(this,
                                 windowTitle(),
                                 tr("A parametere with same name alerty exists."),
                                 QMessageBox::Ok);
    } else {
        if(!d->paremetere)
            d->paremetere = new Parametere();

        d->paremetere->setObjectName(lineEditName->text());
        d->paremetere->setDefaultValue(lineEditDefValue->text());
        d->paremetere->setType(TypeHelper::stringToType(comboBoxType->currentText()));

        accept();
    }
}

LEAF_END_NAMESPACE
