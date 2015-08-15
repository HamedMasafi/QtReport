#ifndef QREPORTPROPERTYPAGEWIDGET_H
#define QREPORTPROPERTYPAGEWIDGET_H

#include "qreportpropertypagebase.h"
#include "ui_qreportpropertypagewidget.h"

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

#endif // QREPORTPROPERTYPAGEWIDGET_H
