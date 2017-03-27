#ifndef QREPORTPANEL_H
#define QREPORTPANEL_H

#include "qreportrectanglebase.h"

LEAF_BEGIN_NAMESPACE

class QReportPanel : public QReportRectangle
{
    Q_OBJECT

public:
    explicit QReportPanel(QGraphicsItem *parent = 0);

    QList<QReportWidgetBase*>   *childs();

public slots:
    void reorderChilds();

protected:
    QList<QReportWidgetBase*>   _childs;

};

LEAF_END_NAMESPACE

#endif // QREPORTPANEL_H
