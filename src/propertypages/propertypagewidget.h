#ifndef QREPORTPROPERTYPAGEWIDGET_H
#define QREPORTPROPERTYPAGEWIDGET_H

#include "propertypages/propertypagebase.h"
#include "ui_propertypagewidget.h"

LEAF_BEGIN_NAMESPACE

class PropertyPageWidget : public PropertyPageBase, private Ui::LReportPropertyPageWidget
{
    Q_OBJECT

public:
    explicit PropertyPageWidget(QWidget *parent = 0);
    ~PropertyPageWidget();

    void save();
    void load();

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEWIDGET_H
