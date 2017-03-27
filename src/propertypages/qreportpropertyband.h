#ifndef QREPORTPROPERTYBAND_H
#define QREPORTPROPERTYBAND_H

#include "ui_qreportpropertyband.h"
#include "qreportpropertypagebase.h"

LEAF_BEGIN_NAMESPACE

class QReportBand;
class QReportPropertyBand : public QReportPropertyPageBase, private Ui::QReportPropertyBand
{
    Q_OBJECT

    QReportBand *_band;

public:
    explicit QReportPropertyBand(QWidget *parent = 0);

    void load();
    void save();

    QReportBand *band() const;
    void setBand(QReportBand *band);

protected:
    void changeEvent(QEvent *e);
};

LEAF_END_NAMESPACE

#endif // QREPORTPROPERTYBAND_H
