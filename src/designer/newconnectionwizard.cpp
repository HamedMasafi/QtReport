#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>

#include "newconnectionwizard.h"

NewConnectionWizard::NewConnectionWizard(QWidget *parent) :
    QWizard(parent)
{
    setupUi(this);

    QStringList drivers = QSqlDatabase::drivers();

    for( int i = 0; i < drivers.count(); i++ )
        comboBoxDrivers->addItem( drivers.at(i) );
}

void NewConnectionWizard::changeEvent(QEvent *e)
{
    QWizard::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void NewConnectionWizard::on_pushButtonTestConnection_clicked()
{
    test(true, true);
}

bool NewConnectionWizard::test(bool showOKMessage, bool showErrorMessage)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(
                comboBoxDrivers->currentText(),
                "testConnection");

    db.setHostName      (lineEditServerName->text());
    db.setDatabaseName  (lineEditDatabase->text());
    db.setUserName      (lineEditUsername->text());
    db.setPassword      (lineEditPassword->text());
    bool ok = db.open();

    if( ok ){
        if(showOKMessage)
            QMessageBox::information( this,
                                      tr( "Test connection" ),
                                      tr( "Connection OK" ) );

        db.close();
    } else {
        if(showErrorMessage){
            QMessageBox warning;
//            warning.setParent(parentWidget());
            warning.setWindowTitle(tr("Test connection" ));
            warning.setText(tr("Error while connection. Please check your configuration and test again."));
            warning.setDetailedText(db.lastError().text() );
            warning.setIcon(QMessageBox::Warning);

            warning.exec();
        }
    }
    QSqlDatabase::removeDatabase( "testConnection" );

    return ok;
}
