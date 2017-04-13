#ifndef QREPORTPROPERTYSORT_H
#define QREPORTPROPERTYSORT_H

<<<<<<< HEAD
#include "ui_propertysort.h"
=======
#include "ui_qreportpropertysort.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93
#include "propertypages/propertypagebase.h"

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
