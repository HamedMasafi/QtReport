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


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "qreportdatabaseinfodialog.h"
#include "qreport.h"
#include "qreportdataconnection.h"

LEAF_BEGIN_NAMESPACE

class QReportDatabaseInfoDialogPrivate
{
public:
    QReportDatabaseInfoDialogPrivate(QReportDatabaseInfoDialog *parent)
        : q_ptr(parent){

    }

    enum Mode{
        New,
        Edit
    };
    Mode mode;

    QReport *report;
    QReportDataConnection *dataConnection;
    bool _isEditMode;
    bool test(bool showOKMessage = true, bool showErrorMessage = true);

private:
    QReportDatabaseInfoDialog *q_ptr;
    Q_DECLARE_PUBLIC(QReportDatabaseInfoDialog)
};

bool QReportDatabaseInfoDialogPrivate::test(bool showOKMessage, bool showErrorMessage)
{
    Q_Q(QReportDatabaseInfoDialog);

    QSqlDatabase db = QSqlDatabase::addDatabase(
                q->comboBoxDrivers->currentText(),
                "testConnection");

    db.setHostName      (q->lineEditServerName->text());
    db.setDatabaseName  (q->lineEditDatabase->text());
    db.setUserName      (q->lineEditUsername->text());
    db.setPassword      (q->lineEditPassword->text());
    bool ok = db.open();

    if( ok ){
        if(showOKMessage)
            QMessageBox::information( q,
                                      QObject::tr( "Test connection" ),
                                      QObject::tr( "Connection OK" ) );
    } else {
        if(showErrorMessage){
            QMessageBox warning;
            warning.setParent(q->parentWidget());
            warning.setWindowTitle(QObject::tr("Test connection" ));
            warning.setText(QObject::tr("Error while connection. Please check your configuration and test again."));
            warning.setDetailedText(db.lastError().text() );
            warning.setIcon(QMessageBox::Warning);

            warning.exec();
        }
        QSqlDatabase::removeDatabase( "testConnection" );
    }

    return ok;
}


QReportDatabaseInfoDialog::QReportDatabaseInfoDialog(QReport *report, QReportDataConnection *dataConnection) :
    QDialog(),
    d_ptr(new QReportDatabaseInfoDialogPrivate(this))
{
    setupUi(this);
    Q_D(QReportDatabaseInfoDialog);
    d->report = report,
    d->dataConnection = dataConnection;
    d->mode = dataConnection ? QReportDatabaseInfoDialogPrivate::Edit : QReportDatabaseInfoDialogPrivate::New;

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    lineEditName->setValidator(validator);

    QStringList drivers = QSqlDatabase::drivers();

    for( int i = 0; i < drivers.count(); i++ )
        comboBoxDrivers->addItem( drivers.at(i) );

//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(d->report->driver()));


}

void QReportDatabaseInfoDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    if( e->type() == QEvent::LanguageChange )
        retranslateUi(this);
}


void QReportDatabaseInfoDialog::on_pushButtonTest_clicked()
{
    Q_D(QReportDatabaseInfoDialog);
    d->test();
}

void QReportDatabaseInfoDialog::on_buttonBox_accepted()
{
    Q_D(QReportDatabaseInfoDialog);

    if(d->mode == d->New && d->report->connection(lineEditName->text())){
        QMessageBox::information(this,
                                 tr("New Connection"),
                                 tr("A connection with same name alerty exists."),
                                 QMessageBox::Ok);
        return;
    }

    if(d->test(false, true))
        this->accept();
}


QReportDataConnection *QReportDatabaseInfoDialog::dataConnection() const
{
    QReportDataConnection *dataConnection = new QReportDataConnection();
    dataConnection->setObjectName(lineEditName->text());
    dataConnection->setServerName(lineEditServerName->text());
    dataConnection->setDatabaseName(lineEditDatabase->text());
    dataConnection->setUsername(lineEditUsername->text());
    dataConnection->setPassword(lineEditPassword->text());
    dataConnection->setDriver(comboBoxDrivers->currentText());
    return dataConnection;
}

void QReportDatabaseInfoDialog::setDataConnection(const QReportDataConnection *dataConnection)
{
    lineEditName->setText(dataConnection->objectName());
    lineEditServerName->setText(dataConnection->serverName());
    lineEditDatabase->setText(dataConnection->databaseName());
    lineEditUsername->setText(dataConnection->username());
    lineEditPassword->setText(dataConnection->password());
    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(dataConnection->driver()));
}



//QString QReportDatabaseInfoDialog::name() const
//{
//    return lineEditName->text();
//}

//void QReportDatabaseInfoDialog::setName(QString name)
//{
//    lineEditName->setText(name);
//}

//QString QReportDatabaseInfoDialog::driver() const
//{
//    return comboBoxDrivers->currentText();
//}

//QString QReportDatabaseInfoDialog::databaseName() const
//{
//    return lineEditDatabase->text();
//}

//QString QReportDatabaseInfoDialog::serverName() const
//{
//    return lineEditServerName->text();
//}

//QString QReportDatabaseInfoDialog::username() const
//{
//    return lineEditUsername->text();
//}

//QString QReportDatabaseInfoDialog::password() const
//{
//    return lineEditPassword->text();
//}

//void QReportDatabaseInfoDialog::setDriver(QString driver)
//{
//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(driver));
//}

//void QReportDatabaseInfoDialog::setDatabaseName(QString databaseName)
//{
//    lineEditDatabase->setText(databaseName);
//}

//void QReportDatabaseInfoDialog::setServerName(QString serverName)
//{
//    lineEditServerName->setText(serverName);
//}

//void QReportDatabaseInfoDialog::setUsername(QString username)
//{
//    lineEditUsername->setText(username);
//}

//void QReportDatabaseInfoDialog::setPassword(QString password)
//{
//    lineEditPassword->setText(password);
//}

//void QReportDatabaseInfoDialog::setDatabaseInfo( QString driver,
//                                                 QString database, QString serverName,
//                                                 QString username, QString password )
//{
//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(driver));
//    lineEditDatabase->setText(database);
//    lineEditServerName->setText(serverName);
//    lineEditUsername->setText(username);
//    lineEditPassword->setText(password);
//}

LEAF_END_NAMESPACE
