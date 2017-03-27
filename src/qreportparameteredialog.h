#ifndef QREPORTPARAMETEREDIALOG_H
#define QREPORTPARAMETEREDIALOG_H

#include "qtreportglobal.h"
#include "ui_qreportparameteredialog.h"

LEAF_BEGIN_NAMESPACE

class LReport;
class LReportParametere;
class LReportParametereDialogPrivate;
class LReportParametereDialog : public QDialog, private Ui::LReportParametereDialog
{
    Q_OBJECT
    LReportParametereDialogPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(LReportParametereDialog)

public:
    explicit LReportParametereDialog(LReport *report, LReportParametere *param = 0);

    LReportParametere *parametere() const;

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_accepted();
};

LEAF_END_NAMESPACE

#endif // QREPORTPARAMETEREDIALOG_H
