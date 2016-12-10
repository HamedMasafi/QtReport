#ifndef QREPORTPROPERTYPAGEPOS_H
#define QREPORTPROPERTYPAGEPOS_H

#include "qreportpropertypagebase.h"
#include "ui_qreportpropertypagepos.h"

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

#endif // QREPORTPROPERTYPAGEPOS_H
