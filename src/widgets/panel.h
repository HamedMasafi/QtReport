#ifndef QREPORTPANEL_H
#define QREPORTPANEL_H

#include "rectanglebase.h"

LEAF_BEGIN_NAMESPACE

class LReportPanel : public LReportRectangle
{
    Q_OBJECT

public:
    explicit LReportPanel(QGraphicsItem *parent = 0);

    QList<LReportWidgetBase*>   *childs();

public slots:
    void reorderChilds();

protected:
    QList<LReportWidgetBase*>   _childs;

};

LEAF_END_NAMESPACE

#endif // QREPORTPANEL_H
