#include "propertypages/propertypagebarcode.h"
#include "ui_propertypagebarcode.h"

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
