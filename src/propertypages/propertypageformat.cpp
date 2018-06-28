#include "propertypages/propertypageformat.h"

LEAF_BEGIN_NAMESPACE

PropertyPageFormat::PropertyPageFormat(QWidget *parent) :
      PropertyPageBase(parent)
{
    setupUi(this);

    _title = tr( "Format" );
}

void PropertyPageFormat::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    if (e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

void PropertyPageFormat::load()
{

}

void PropertyPageFormat::save()
{

}

LEAF_END_NAMESPACE
