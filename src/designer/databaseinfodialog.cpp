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
#include "databaseinfodialog.h"
#include "core/report.h"
#include "dataconnection.h"

LEAF_BEGIN_NAMESPACE

class DatabaseInfoDialogPrivate
{
public:
    DatabaseInfoDialogPrivate(DatabaseInfoDialog *parent)
        : q_ptr(parent){

    }

    enum Mode{
        New,
        Edit
    };
    Mode mode;

    Report *report;
    DataConnection *dataConnection;
    bool _isEditMode;
    bool test(bool showOKMessage = true, bool showErrorMessage = true);

private:
    DatabaseInfoDialog *q_ptr;
    Q_DECLARE_PUBLIC(DatabaseInfoDialog)
};

bool DatabaseInfoDialogPrivate::test(bool showOKMessage, bool showErrorMessage)
{
    Q_Q(DatabaseInfoDialog);

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


DatabaseInfoDialog::DatabaseInfoDialog(Report *report, DataConnection *dataConnection) :
    QDialog(),
    d_ptr(new DatabaseInfoDialogPrivate(this))
{
    setupUi(this);
    Q_D(DatabaseInfoDialog);
    d->report = report,
    d->dataConnection = dataConnection;
    d->mode = dataConnection ? DatabaseInfoDialogPrivate::Edit : DatabaseInfoDialogPrivate::New;

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    lineEditName->setValidator(validator);

    QStringList drivers = QSqlDatabase::drivers();

    for( int i = 0; i < drivers.count(); i++ )
        comboBoxDrivers->addItem( drivers.at(i) );

//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(d->report->driver()));


}

void DatabaseInfoDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    if( e->type() == QEvent::LanguageChange )
        retranslateUi(this);
}


void DatabaseInfoDialog::on_pushButtonTest_clicked()
{
    Q_D(DatabaseInfoDialog);
    d->test();
}

void DatabaseInfoDialog::on_buttonBox_accepted()
{
    Q_D(DatabaseInfoDialog);

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


DataConnection *DatabaseInfoDialog::dataConnection() const
{
    DataConnection *dataConnection = new DataConnection();
    dataConnection->setObjectName(lineEditName->text());
    dataConnection->setServerName(lineEditServerName->text());
    dataConnection->setDatabaseName(lineEditDatabase->text());
    dataConnection->setUsername(lineEditUsername->text());
    dataConnection->setPassword(lineEditPassword->text());
    dataConnection->setDriver(comboBoxDrivers->currentText());
    return dataConnection;
}

void DatabaseInfoDialog::setDataConnection(const DataConnection *dataConnection)
{
    lineEditName->setText(dataConnection->objectName());
    lineEditServerName->setText(dataConnection->serverName());
    lineEditDatabase->setText(dataConnection->databaseName());
    lineEditUsername->setText(dataConnection->username());
    lineEditPassword->setText(dataConnection->password());
    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(dataConnection->driver()));
}



//QString DatabaseInfoDialog::name() const
//{
//    return lineEditName->text();
//}

//void DatabaseInfoDialog::setName(QString name)
//{
//    lineEditName->setText(name);
//}

//QString DatabaseInfoDialog::driver() const
//{
//    return comboBoxDrivers->currentText();
//}

//QString DatabaseInfoDialog::databaseName() const
//{
//    return lineEditDatabase->text();
//}

//QString DatabaseInfoDialog::serverName() const
//{
//    return lineEditServerName->text();
//}

//QString DatabaseInfoDialog::username() const
//{
//    return lineEditUsername->text();
//}

//QString DatabaseInfoDialog::password() const
//{
//    return lineEditPassword->text();
//}

//void DatabaseInfoDialog::setDriver(QString driver)
//{
//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(driver));
//}

//void DatabaseInfoDialog::setDatabaseName(QString databaseName)
//{
//    lineEditDatabase->setText(databaseName);
//}

//void DatabaseInfoDialog::setServerName(QString serverName)
//{
//    lineEditServerName->setText(serverName);
//}

//void DatabaseInfoDialog::setUsername(QString username)
//{
//    lineEditUsername->setText(username);
//}

//void DatabaseInfoDialog::setPassword(QString password)
//{
//    lineEditPassword->setText(password);
//}

//void DatabaseInfoDialog::setDatabaseInfo( QString driver,
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
