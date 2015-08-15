#include "qreportpropertypageformat.h"

QReportPropertyPageFormat::QReportPropertyPageFormat(QWidget *parent) :
      QReportPropertyPageBase(parent)
{
    setupUi(this);

    _title = tr( "Format" );
}

void QReportPropertyPageFormat::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void QReportPropertyPageFormat::load()
{

}

void QReportPropertyPageFormat::save()
{

}
