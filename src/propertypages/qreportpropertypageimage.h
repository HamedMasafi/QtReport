#ifndef QREPORTPROPERTYPAGEIMAGE_H
#define QREPORTPROPERTYPAGEIMAGE_H

class QPixmap;

#include "qreportpropertypagebase.h"
#include "ui_qreportpropertypageimage.h"

LEAF_BEGIN_NAMESPACE

class QReportPropertyPageImage : public QReportPropertyPageBase, private Ui::QReportPropertyPageImage
{
    Q_OBJECT

public:
    QReportPropertyPageImage(QWidget *parent = 0);

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
