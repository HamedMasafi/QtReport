#include "propertysort.h"

#include <QItemDelegate>

LEAF_BEGIN_NAMESPACE

PropertySort::PropertySort(QWidget *parent) :
    PropertyPageBase(parent)
{
    _title = tr("Sort");
    setupUi(this);

    QItemDelegate *delegate = new QItemDelegate();

//    tableWidget->setItemDelegate();
}

void PropertySort::save()
{

}

void PropertySort::load()
{
}

void PropertySort::changeEvent(QEvent *e)
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
