#ifndef QREPORTPROPERTYSORT_H
#define QREPORTPROPERTYSORT_H

#include "ui_propertysort.h"
#include "propertypages/propertypagebase.h"

LEAF_BEGIN_NAMESPACE

class PropertySort : public PropertyPageBase, private Ui::LReportPropertySort
{
    Q_OBJECT

public:
    explicit PropertySort(QWidget *parent = 0);

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYSORT_H
