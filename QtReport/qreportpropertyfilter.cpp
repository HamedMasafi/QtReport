#include "qreportpropertyfilter.h"

QReportPropertyFilter::QReportPropertyFilter(QWidget *parent) :
    QReportPropertyPageBase(parent)
{
    _title = tr("Filter");
    setupUi(this);
}

void QReportPropertyFilter::load()
{

}

void QReportPropertyFilter::save()
{

}

void QReportPropertyFilter::changeEvent(QEvent *e)
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
