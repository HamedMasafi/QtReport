#include "propertyfilter.h"

LEAF_BEGIN_NAMESPACE

PropertyFilter::PropertyFilter(QWidget *parent) :
    PropertyPageBase(parent)
{
    _title = tr("Filter");
    setupUi(this);
}

void PropertyFilter::load()
{

}

void PropertyFilter::save()
{

}

void PropertyFilter::changeEvent(QEvent *e)
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
