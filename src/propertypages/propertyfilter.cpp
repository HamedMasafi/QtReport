#include "propertyfilter.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyFilter::LReportPropertyFilter(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    _title = tr("Filter");
    setupUi(this);
}

void LReportPropertyFilter::load()
{

}

void LReportPropertyFilter::save()
{

}

void LReportPropertyFilter::changeEvent(QEvent *e)
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

LEAF_END_NAMESPACE
