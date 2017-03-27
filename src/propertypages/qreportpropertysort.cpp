#include "qreportpropertysort.h"

#include <QItemDelegate>

LEAF_BEGIN_NAMESPACE

LReportPropertySort::LReportPropertySort(QWidget *parent) :
    LReportPropertyPageBase(parent)
{
    _title = tr("Sort");
    setupUi(this);

    QItemDelegate *delegate = new QItemDelegate();

//    tableWidget->setItemDelegate();
}

void LReportPropertySort::save()
{

}

void LReportPropertySort::load()
{
}

void LReportPropertySort::changeEvent(QEvent *e)
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
