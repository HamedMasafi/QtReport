#ifndef QREPORTPARAMETEREDIALOG_H
#define QREPORTPARAMETEREDIALOG_H

#include "qtreportglobal.h"
#include "ui_qreportparameteredialog.h"

LEAF_BEGIN_NAMESPACE

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

LEAF_END_NAMESPACE

#endif // QREPORTPARAMETEREDIALOG_H
