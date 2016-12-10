#include "qreportpropertysort.h"

#include <QItemDelegate>

QReportPropertySort::QReportPropertySort(QWidget *parent) :
    QReportPropertyPageBase(parent)
{
    _title = tr("Sort");
    setupUi(this);

    QItemDelegate *delegate = new QItemDelegate();

//    tableWidget->setItemDelegate();
}

void QReportPropertySort::save()
{

}

void QReportPropertySort::load()
{
}

void QReportPropertySort::changeEvent(QEvent *e)
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
