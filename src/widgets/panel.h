#ifndef QREPORTPANEL_H
#define QREPORTPANEL_H

#include "rectanglebase.h"

LEAF_BEGIN_NAMESPACE

class Panel : public Rectangle
{
    Q_OBJECT

public:
    explicit Panel(QGraphicsItem *parent = 0);

    QList<WidgetBase*>   *childs();

public slots:
    void reorderChilds();

protected:
    QList<WidgetBase*>   _childs;

};

LEAF_END_NAMESPACE

#endif // QREPORTPANEL_H
