#include "propertypages/propertypagebarcode.h"
<<<<<<< HEAD
#include "ui_propertypagebarcode.h"
=======
#include "ui_qreportpropertypagebarcode.h"
>>>>>>> d6ccb8904f16d3c0ba28fe1f38048a467b682a93

LReportPropertyPageBarcode::LReportPropertyPageBarcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LReportPropertyPageBarcode)
{
    ui->setupUi(this);
}

LReportPropertyPageBarcode::~LReportPropertyPageBarcode()
{
    delete ui;
}
