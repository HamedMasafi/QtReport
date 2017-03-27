#ifndef QREPORTPROPERTYPAGEFORMAT_H
#define QREPORTPROPERTYPAGEFORMAT_H

#include "propertypages/qreportpropertypagebase.h"
#include "ui_qreportpropertypageformat.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertyPageFormat : public LReportPropertyPageBase, private Ui::LReportPropertyPageFormat
{
    Q_OBJECT

public:
    explicit LReportPropertyPageFormat(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);

};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEFORMAT_H
