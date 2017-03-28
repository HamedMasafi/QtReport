#ifndef QREPORTPROPERTYFILTER_H
#define QREPORTPROPERTYFILTER_H

#include "ui_qreportpropertyfilter.h"
#include "propertypages/propertypagebase.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertyFilter : public LReportPropertyPageBase, private Ui::LReportPropertyFilter
{
    Q_OBJECT

public:
    explicit LReportPropertyFilter(QWidget *parent = 0);

    void load();
    void save();


protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYFILTER_H
