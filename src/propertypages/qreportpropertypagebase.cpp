
#include <QLabel>

#include "qreportpropertypagebase.h"
#include "qreportwidgetbase.h"

LEAF_BEGIN_NAMESPACE

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

LEAF_END_NAMESPACE
