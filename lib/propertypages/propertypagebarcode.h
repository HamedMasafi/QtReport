#ifndef QREPORTPROPERTYPAGEBARCODE_H
#define QREPORTPROPERTYPAGEBARCODE_H

#include <QWidget>

namespace Ui {
    class PropertyPageBarcode;
}

class PropertyPageBarcode : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyPageBarcode(QWidget *parent = 0);
    ~PropertyPageBarcode();

private:
    Ui::PropertyPageBarcode *ui;
};

#endif // QREPORTPROPERTYPAGEBARCODE_H
