
#include <QLabel>

#include "widgets/qreportwidgetbase.h"
#include "qreportdocumentdesigner.h"
#include "propertypages/qreportpropertypagebase.h"
#include "widgets/qreportwidgetbase.h"

LEAF_BEGIN_NAMESPACE

LReportPropertyPageBase::LReportPropertyPageBase(QWidget *parent) :
    QWidget(parent)
{
}


bool LReportPropertyPageBase::isChanged() const
{
   return _isChanged;
}

int LReportPropertyPageBase::index() const
{
   return _index;
}

QString LReportPropertyPageBase::title() const
{
   return _title;
}

LReportDocumentDesigner *LReportPropertyPageBase::designer() const
{
    return _designer;
}

void LReportPropertyPageBase::setDesigner(LReportDocumentDesigner *designer)
{
    _designer = designer;
}

LEAF_END_NAMESPACE

