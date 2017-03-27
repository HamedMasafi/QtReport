#include "propertypages/qreportpropertypagepos.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPagePos::LReportPropertyPagePos(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    setupUi(this);

    _title = tr( "Position" );
}

void LReportPropertyPagePos::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}


void LReportPropertyPagePos::load()
{
//   doubleSpinBoxLeft->setValue( widget->pos().x() );
//   doubleSpinBoxTop->setValue( widget->pos().y() );
//   doubleSpinBoxWidth->setValue( widget->size().width() );
//   doubleSpinBoxHeight->setValue( widget->size().height() );
}

void LReportPropertyPagePos::save()
{
//   widget->setPos(  doubleSpinBoxLeft->value(), doubleSpinBoxTop->value() );
//   widget->setSize( doubleSpinBoxWidth->value(), doubleSpinBoxHeight->value() );
}

LEAF_END_NAMESPACE
