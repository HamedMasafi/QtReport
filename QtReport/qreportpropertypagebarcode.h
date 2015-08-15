#ifndef QREPORTPROPERTYPAGEBARCODE_H
#define QREPORTPROPERTYPAGEBARCODE_H

#include <QWidget>

namespace Ui {
    class QReportPropertyPageBarcode;
}

class QReportPropertyPageBarcode : public QWidget
{
    Q_OBJECT

public:
    explicit QReportPropertyPageBarcode(QWidget *parent = 0);
    ~QReportPropertyPageBarcode();

private:
    Ui::QReportPropertyPageBarcode *ui;
};

#endif // QREPORTPROPERTYPAGEBARCODE_H
