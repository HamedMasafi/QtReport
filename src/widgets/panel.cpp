#include "panel.h"

LEAF_BEGIN_NAMESPACE

Panel::Panel(QGraphicsItem *parent):
    Rectangle(parent)
{
    setMinimumSize(20, 20);
}

void Panel::reorderChilds()
{
    foreach(WidgetBase  *widget, _childs) {
        QPointF pt = mapToScene(widget->childPos());
        widget->setPos(pt);
    }//foreach
}

QList<WidgetBase*> *Panel::childs()
{
    return &_childs;
}

LEAF_END_NAMESPACE
