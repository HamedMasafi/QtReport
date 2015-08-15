
#include <QLabel>

#include "qreportpropertypagebase.h"
#include "qreportwidgetbase.h"



QReportPropertyPageBase::QReportPropertyPageBase(QWidget *parent) :
    QWidget(parent)
{
}


bool QReportPropertyPageBase::isChanged() const
{
   return _isChanged;
}

int QReportPropertyPageBase::index() const
{
   return _index;
}

QString QReportPropertyPageBase::title() const
{
   return _title;
}


void QReportPropertyPageBase::setDesigner(QReportDocumentDesigner *designer)
{
   _designer = designer;
}
