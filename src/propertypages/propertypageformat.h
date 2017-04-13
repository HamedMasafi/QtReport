#ifndef QREPORTPROPERTYPAGEFORMAT_H
#define QREPORTPROPERTYPAGEFORMAT_H

#include "propertypages/propertypagebase.h"
<<<<<<< HEAD
#include "ui_propertypageformat.h"
=======
#include "ui_qreportpropertypageformat.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93

LEAF_BEGIN_NAMESPACE

class LReportPropertyPageFormat : public LReportPropertyPageBase, private Ui::LReportPropertyPageFormat
{
    Q_OBJECT

public:
    explicit LReportPropertyPageFormat(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);

};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEFORMAT_H
