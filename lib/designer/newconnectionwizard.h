#ifndef NEWCONNECTIONWIZARD_H
#define NEWCONNECTIONWIZARD_H

#include "ui_newconnectionwizard.h"

class NewConnectionWizard : public QWizard, private Ui::NewConnectionWizard
{
    Q_OBJECT

    bool test(bool showOKMessage, bool showErrorMessage);
public:
    explicit NewConnectionWizard(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *e);
private slots:
    void on_pushButtonTestConnection_clicked();
};

#endif // NEWCONNECTIONWIZARD_H
