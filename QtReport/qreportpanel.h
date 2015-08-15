#ifndef QREPORTPANEL_H
#define QREPORTPANEL_H

#include "qreportrectanglebase.h"

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

#endif // QREPORTPANEL_H
