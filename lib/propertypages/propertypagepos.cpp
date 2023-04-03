#include "propertypages/propertypagepos.h"

LEAF_BEGIN_NAMESPACE

PropertyPagePos::PropertyPagePos(QWidget *parent) :
    PropertyPageBase(parent)
{
    setupUi(this);

    _title = tr( "Position" );
}

void PropertyPagePos::changeEvent(QEvent *e)
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


void PropertyPagePos::load()
{
//   doubleSpinBoxLeft->setValue( widget->pos().x() );
//   doubleSpinBoxTop->setValue( widget->pos().y() );
//   doubleSpinBoxWidth->setValue( widget->size().width() );
//   doubleSpinBoxHeight->setValue( widget->size().height() );
}

void PropertyPagePos::save()
{
//   widget->setPos(  doubleSpinBoxLeft->value(), doubleSpinBoxTop->value() );
//   widget->setSize( doubleSpinBoxWidth->value(), doubleSpinBoxHeight->value() );
}

LEAF_END_NAMESPACE
