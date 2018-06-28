#ifndef QREPORTPROPERTYFILTER_H
#define QREPORTPROPERTYFILTER_H

#include "ui_propertyfilter.h"
#include "propertypages/propertypagebase.h"

LEAF_BEGIN_NAMESPACE

class PropertyFilter : public PropertyPageBase, private Ui::LReportPropertyFilter
{
    Q_OBJECT

public:
    explicit PropertyFilter(QWidget *parent = 0);

    void load();
    void save();


protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYFILTER_H
