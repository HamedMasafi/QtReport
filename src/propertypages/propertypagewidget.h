#ifndef QREPORTPROPERTYPAGEWIDGET_H
#define QREPORTPROPERTYPAGEWIDGET_H

#include "propertypages/propertypagebase.h"
#include "ui_qreportpropertypagewidget.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertyPageWidget : public LReportPropertyPageBase, private Ui::LReportPropertyPageWidget
{
    Q_OBJECT

public:
    explicit LReportPropertyPageWidget(QWidget *parent = 0);
    ~LReportPropertyPageWidget();

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEWIDGET_H
