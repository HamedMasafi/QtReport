#ifndef QREPORTPROPERTYFILTER_H
#define QREPORTPROPERTYFILTER_H

<<<<<<< HEAD
#include "ui_propertyfilter.h"
=======
#include "ui_qreportpropertyfilter.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93
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
