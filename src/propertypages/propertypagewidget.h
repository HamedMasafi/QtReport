#ifndef QREPORTPROPERTYPAGEWIDGET_H
#define QREPORTPROPERTYPAGEWIDGET_H

#include "propertypages/propertypagebase.h"
<<<<<<< HEAD
#include "ui_propertypagewidget.h"
=======
#include "ui_qreportpropertypagewidget.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93

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
