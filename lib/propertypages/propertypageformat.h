#ifndef QREPORTPROPERTYPAGEFORMAT_H
#define QREPORTPROPERTYPAGEFORMAT_H

#include "propertypages/propertypagebase.h"
#include "ui_propertypageformat.h"

LEAF_BEGIN_NAMESPACE

class PropertyPageFormat : public PropertyPageBase, private Ui::LReportPropertyPageFormat
{
    Q_OBJECT

public:
    explicit PropertyPageFormat(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);

};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEFORMAT_H
