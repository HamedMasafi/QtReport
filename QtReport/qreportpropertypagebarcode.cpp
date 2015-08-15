#include "qreportpropertypagebarcode.h"
#include "ui_qreportpropertypagebarcode.h"

QReportPropertyPageBarcode::QReportPropertyPageBarcode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QReportPropertyPageBarcode)
{
    ui->setupUi(this);
}

QReportPropertyPageBarcode::~QReportPropertyPageBarcode()
{
    delete ui;
}
