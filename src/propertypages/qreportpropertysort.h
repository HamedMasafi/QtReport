#ifndef QREPORTPROPERTYSORT_H
#define QREPORTPROPERTYSORT_H

#include "ui_qreportpropertysort.h"
#include "propertypages/qreportpropertypagebase.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertySort : public LReportPropertyPageBase, private Ui::LReportPropertySort
{
    Q_OBJECT

public:
    explicit LReportPropertySort(QWidget *parent = 0);

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYSORT_H
