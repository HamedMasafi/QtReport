#ifndef QREPORTPROPERTYPAGEPOS_H
#define QREPORTPROPERTYPAGEPOS_H

#include "propertypages/propertypagebase.h"
#include "ui_propertypagepos.h"

LEAF_BEGIN_NAMESPACE

class PropertyPagePos : public PropertyPageBase, private Ui::LReportPropertyPagePos
{
    Q_OBJECT

public:
    PropertyPagePos(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEPOS_H
