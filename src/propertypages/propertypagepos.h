#ifndef QREPORTPROPERTYPAGEPOS_H
#define QREPORTPROPERTYPAGEPOS_H

#include "propertypages/propertypagebase.h"
#include "ui_qreportpropertypagepos.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertyPagePos : public LReportPropertyPageBase, private Ui::LReportPropertyPagePos
{
    Q_OBJECT

public:
    LReportPropertyPagePos(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEPOS_H
