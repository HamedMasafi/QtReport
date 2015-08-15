#include "qreportpropertyband.h"
#include "qreportsectiondataproperties.h"

#include <qreportband.h>
#include "qreport.h"

QReportBand *QReportPropertyBand::band() const
{
    return _band;
}

void QReportPropertyBand::setBand(QReportBand *band)
{
    _band = band;
    QWidget *w = 0;

    switch(band->bandType()){
    case ::Data:
        w = new QReportSectionDataProperties();
        qDebug() << "------------------------------";
        break;
    }

    if(w)
    widgetPropertyPage->layout()->addWidget(w);
}
QReportPropertyBand::QReportPropertyBand(QWidget *parent) :
    QReportPropertyPageBase(parent)
{
    _title = tr("Band properties");
    setupUi(this);
}

void QReportPropertyBand::load()
{
    foreach (QReportDataTable *table, _designer->report()->dataTables())
        comboBox->addItem(table->objectName());
}

void QReportPropertyBand::save()
{

}

void QReportPropertyBand::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
