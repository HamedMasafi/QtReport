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

class LReportDatabaseInfoDialogPrivate
{
public:
    LReportDatabaseInfoDialogPrivate(LReportDatabaseInfoDialog *parent)
        : q_ptr(parent){

    }

    enum Mode{
        New,
        Edit
    };
    Mode mode;

    LReport *report;
    LReportDataConnection *dataConnection;
    bool _isEditMode;
    bool test(bool showOKMessage = true, bool showErrorMessage = true);

private:
    LReportDatabaseInfoDialog *q_ptr;
    Q_DECLARE_PUBLIC(LReportDatabaseInfoDialog)
};

bool LReportDatabaseInfoDialogPrivate::test(bool showOKMessage, bool showErrorMessage)
{
    Q_Q(LReportDatabaseInfoDialog);

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


LReportDatabaseInfoDialog::LReportDatabaseInfoDialog(LReport *report, LReportDataConnection *dataConnection) :
    QDialog(),
    d_ptr(new LReportDatabaseInfoDialogPrivate(this))
{
    setupUi(this);
    Q_D(LReportDatabaseInfoDialog);
    d->report = report,
    d->dataConnection = dataConnection;
    d->mode = dataConnection ? LReportDatabaseInfoDialogPrivate::Edit : LReportDatabaseInfoDialogPrivate::New;

    QValidator *validator = new QRegExpValidator(QRegExp("[A-Za-z][\\d\\w]+"), this);
    lineEditName->setValidator(validator);

    QStringList drivers = QSqlDatabase::drivers();

    for( int i = 0; i < drivers.count(); i++ )
        comboBoxDrivers->addItem( drivers.at(i) );

//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(d->report->driver()));


}

void LReportDatabaseInfoDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);

    if( e->type() == QEvent::LanguageChange )
        retranslateUi(this);
}


void LReportDatabaseInfoDialog::on_pushButtonTest_clicked()
{
    Q_D(LReportDatabaseInfoDialog);
    d->test();
}

void LReportDatabaseInfoDialog::on_buttonBox_accepted()
{
    Q_D(LReportDatabaseInfoDialog);

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


LReportDataConnection *LReportDatabaseInfoDialog::dataConnection() const
{
    LReportDataConnection *dataConnection = new LReportDataConnection();
    dataConnection->setObjectName(lineEditName->text());
    dataConnection->setServerName(lineEditServerName->text());
    dataConnection->setDatabaseName(lineEditDatabase->text());
    dataConnection->setUsername(lineEditUsername->text());
    dataConnection->setPassword(lineEditPassword->text());
    dataConnection->setDriver(comboBoxDrivers->currentText());
    return dataConnection;
}

void LReportDatabaseInfoDialog::setDataConnection(const LReportDataConnection *dataConnection)
{
    lineEditName->setText(dataConnection->objectName());
    lineEditServerName->setText(dataConnection->serverName());
    lineEditDatabase->setText(dataConnection->databaseName());
    lineEditUsername->setText(dataConnection->username());
    lineEditPassword->setText(dataConnection->password());
    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(dataConnection->driver()));
}



//QString LReportDatabaseInfoDialog::name() const
//{
//    return lineEditName->text();
//}

//void LReportDatabaseInfoDialog::setName(QString name)
//{
//    lineEditName->setText(name);
//}

//QString LReportDatabaseInfoDialog::driver() const
//{
//    return comboBoxDrivers->currentText();
//}

//QString LReportDatabaseInfoDialog::databaseName() const
//{
//    return lineEditDatabase->text();
//}

//QString LReportDatabaseInfoDialog::serverName() const
//{
//    return lineEditServerName->text();
//}

//QString LReportDatabaseInfoDialog::username() const
//{
//    return lineEditUsername->text();
//}

//QString LReportDatabaseInfoDialog::password() const
//{
//    return lineEditPassword->text();
//}

//void LReportDatabaseInfoDialog::setDriver(QString driver)
//{
//    comboBoxDrivers->setCurrentIndex(comboBoxDrivers->findText(driver));
//}

//void LReportDatabaseInfoDialog::setDatabaseName(QString databaseName)
//{
//    lineEditDatabase->setText(databaseName);
//}

//void LReportDatabaseInfoDialog::setServerName(QString serverName)
//{
//    lineEditServerName->setText(serverName);
//}

//void LReportDatabaseInfoDialog::setUsername(QString username)
//{
//    lineEditUsername->setText(username);
//}

//void LReportDatabaseInfoDialog::setPassword(QString password)
//{
//    lineEditPassword->setText(password);
//}

//void LReportDatabaseInfoDialog::setDatabaseInfo( QString driver,
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
