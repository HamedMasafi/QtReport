#ifndef QREPORTPROPERTYSORT_H
#define QREPORTPROPERTYSORT_H

#include "ui_qreportpropertysort.h"
#include "qreportpropertypagebase.h"

LEAF_BEGIN_NAMESPACE

class QReportPropertySort : public QReportPropertyPageBase, private Ui::QReportPropertySort
{
    Q_OBJECT

public:
    explicit QReportPropertySort(QWidget *parent = 0);

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYSORT_H
