#ifndef QREPORTPROPERTYPAGEWIDGET_H
#define QREPORTPROPERTYPAGEWIDGET_H

#include "qreportpropertypagebase.h"
#include "ui_qreportpropertypagewidget.h"

LEAF_BEGIN_NAMESPACE

class QReportPropertyPageWidget : public QReportPropertyPageBase, private Ui::QReportPropertyPageWidget
{
    Q_OBJECT

public:
    explicit QReportPropertyPageWidget(QWidget *parent = 0);
    ~QReportPropertyPageWidget();

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEWIDGET_H
