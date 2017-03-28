#include "propertypages/propertypageformat.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPageFormat::LReportPropertyPageFormat(QWidget *parent) :
      LReportPropertyPageBase(parent)
{
    setupUi(this);

    _title = tr( "Format" );
}

void LReportPropertyPageFormat::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void LReportPropertyPageFormat::load()
{

}

void LReportPropertyPageFormat::save()
{

}

LEAF_END_NAMESPACE
