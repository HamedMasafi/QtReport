#ifndef QREPORTPARAMETEREDIALOG_H
#define QREPORTPARAMETEREDIALOG_H

#include "qtreportglobal.h"
#include "ui_parameteredialog.h"

LEAF_BEGIN_NAMESPACE

class Report;
class Parametere;
class ParametereDialogPrivate;
class ParametereDialog : public QDialog, private Ui::LReportParametereDialog
{
    Q_OBJECT
    ParametereDialogPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(ParametereDialog)

public:
    explicit ParametereDialog(Report *report, Parametere *param = 0);

    Parametere *parametere() const;

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_accepted();
};

LEAF_END_NAMESPACE

#endif // QREPORTPARAMETEREDIALOG_H
