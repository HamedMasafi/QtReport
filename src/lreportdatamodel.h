#ifndef LREPORTDATAMODEL_H
#define LREPORTDATAMODEL_H

#include <QObject>

class LReportDataModel : public QObject
{
    Q_OBJECT
public:
    explicit LReportDataModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LREPORTDATAMODEL_H