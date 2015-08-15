#include "qreportpanel.h"

QReportPanel::QReportPanel(QGraphicsItem *parent):
    QReportRectangle(parent)
{
    setMinimumSize(20, 20);
}



void QReportPanel::reorderChilds()
{
    foreach(QReportWidgetBase  *widget, _childs) {
        QPointF pt = mapToScene(widget->childPos());
        widget->setPos(pt);
    }//foreach
}



QList<QReportWidgetBase*> *QReportPanel::childs()
{
    return &_childs;
}



