#ifndef QREPORTPROPERTYPAGEBARCODE_H
#define QREPORTPROPERTYPAGEBARCODE_H

#include <QWidget>

namespace Ui {
    class LReportPropertyPageBarcode;
}

class LReportPropertyPageBarcode : public QWidget
{
    Q_OBJECT

public:
    explicit LReportPropertyPageBarcode(QWidget *parent = 0);
    ~LReportPropertyPageBarcode();

private:
    Ui::LReportPropertyPageBarcode *ui;
};

#endif // QREPORTPROPERTYPAGEBARCODE_H
