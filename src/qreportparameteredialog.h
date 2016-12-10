#ifndef QREPORTPARAMETEREDIALOG_H
#define QREPORTPARAMETEREDIALOG_H

#include "ui_qreportparameteredialog.h"

class QReport;
class QReportParametere;
class QReportParametereDialogPrivate;
class QReportParametereDialog : public QDialog, private Ui::QReportParametereDialog
{
    Q_OBJECT
    QReportParametereDialogPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(QReportParametereDialog)

public:
    explicit QReportParametereDialog(QReport *report, QReportParametere *param = 0);

    QReportParametere *parametere() const;

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_accepted();
};

#endif // QREPORTPARAMETEREDIALOG_H
