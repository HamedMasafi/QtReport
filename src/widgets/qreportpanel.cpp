#include "qreportpanel.h"

LEAF_BEGIN_NAMESPACE

LReportPanel::LReportPanel(QGraphicsItem *parent):
    LReportRectangle(parent)
{
    setMinimumSize(20, 20);
}

void LReportPanel::reorderChilds()
{
    foreach(LReportWidgetBase  *widget, _childs) {
        QPointF pt = mapToScene(widget->childPos());
        widget->setPos(pt);
    }//foreach
}

QList<LReportWidgetBase*> *LReportPanel::childs()
{
    return &_childs;
}

LEAF_END_NAMESPACE
