#ifndef QREPORTPROPERTYPAGEIMAGE_H
#define QREPORTPROPERTYPAGEIMAGE_H

class QPixmap;

#include "propertypages/qreportpropertypagebase.h"
#include "ui_qreportpropertypageimage.h"

LEAF_BEGIN_NAMESPACE

class LReportPropertyPageImage : public LReportPropertyPageBase, private Ui::LReportPropertyPageImage
{
    Q_OBJECT

public:
    LReportPropertyPageImage(QWidget *parent = 0);

    void load();
    void save();

   QPixmap pixmap;

   void resizeEvent ( QResizeEvent  *event );

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_checkBoxScale_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonBrowse_clicked();
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYPAGEIMAGE_H
