#include "propertypages/propertypagewidget.h"
#include "designer/documentdesigner.h"

LEAF_BEGIN_NAMESPACE

PropertyPageWidget::PropertyPageWidget(QWidget *parent) :
    PropertyPageBase(parent)
{
    setupUi(this);

    _title = tr("General");
}


void PropertyPageWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);

    if( e->type() == QEvent::LanguageChange)
        retranslateUi(this);
}

PropertyPageWidget::~PropertyPageWidget()
{

}

void PropertyPageWidget::save()
{
   _designer->activeWidget()->setObjectName(lineEditWidgetName->text());

   _designer->activeWidget()->setProperty("top",    spinBoxTop->value());
   _designer->activeWidget()->setProperty("left",   spinBoxLeft->value());
   _designer->activeWidget()->setProperty("width",  spinBoxWidth->value());
   _designer->activeWidget()->setProperty("height", spinBoxHeight->value());
}

void PropertyPageWidget::load()
{
   spinBoxTop->setValue(   _designer->widgetProperty("top").toInt());
   spinBoxLeft->setValue(  _designer->widgetProperty("left").toInt());
   spinBoxWidth->setValue( _designer->widgetProperty("width").toInt());
   spinBoxHeight->setValue(_designer->widgetProperty("height").toInt());

   lineEditWidgetName->setText(_designer->activeWidget()->objectName());
}

LEAF_END_NAMESPACE
