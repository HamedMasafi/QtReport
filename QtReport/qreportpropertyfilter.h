#ifndef QREPORTPROPERTYFILTER_H
#define QREPORTPROPERTYFILTER_H

#include "ui_qreportpropertyfilter.h"
#include "qreportpropertypagebase.h"

class QReportPropertyFilter : public QReportPropertyPageBase, private Ui::QReportPropertyFilter
{
    Q_OBJECT

public:
    explicit QReportPropertyFilter(QWidget *parent = 0);

    void load();
    void save();


protected:
    void changeEvent(QEvent *e);
};

#endif // QREPORTPROPERTYFILTER_H
