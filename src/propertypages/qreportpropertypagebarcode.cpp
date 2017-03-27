#include "propertypages/qreportpropertypagebarcode.h"
#include "ui_qreportpropertypagebarcode.h"

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
