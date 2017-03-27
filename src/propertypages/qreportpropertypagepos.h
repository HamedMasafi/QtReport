#ifndef QREPORTPROPERTYPAGEPOS_H
#define QREPORTPROPERTYPAGEPOS_H

#include "qreportpropertypagebase.h"
#include "ui_qreportpropertypagepos.h"

LEAF_BEGIN_NAMESPACE

class QReportPropertyPagePos : public QReportPropertyPageBase, private Ui::QReportPropertyPagePos
{
    Q_OBJECT

public:
    QReportPropertyPagePos(QWidget *parent = 0);

    void load();
    void save();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEPOS_H
