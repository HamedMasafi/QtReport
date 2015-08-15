#ifndef QREPORTPROPERTYSORT_H
#define QREPORTPROPERTYSORT_H

#include "ui_qreportpropertysort.h"
#include "qreportpropertypagebase.h"

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

#endif // QREPORTPROPERTYSORT_H
