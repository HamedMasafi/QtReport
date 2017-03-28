#ifndef LREPORTPRINTSETTINGS_H
#define LREPORTPRINTSETTINGS_H

#include "qtreportglobal.h"
#include <QtCore/QObject>

LEAF_BEGIN_NAMESPACE

class LReportPrintSettingsPrivate;
class LReportPrintSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal marginTop     READ marginTop    WRITE setMarginTop    USER true)
    Q_PROPERTY(qreal marginBottom  READ marginBottom WRITE setMarginBottom USER true)
    Q_PROPERTY(qreal marginLeft    READ marginLeft   WRITE setMarginLeft   USER true)
    Q_PROPERTY(qreal marginRight   READ marginRight  WRITE setMarginRight  USER true)

public:
    LReportPrintSettings();

    qreal marginLeft() const;
    qreal marginBottom() const;
    qreal marginTop() const;
    qreal marginRight() const;

    void setMarginLeft(qreal value);
    void setMarginRight(qreal value);
    void setMarginTop(qreal value);
    void setMarginBottom(qreal value);
    void setMargins(qreal marginLeft, qreal marginTop, qreal marginRight, qreal marginBottom);

    QSizeF designArea() const;
    QSizeF pageSize() const;
    void setSize(QSizeF s);
    void setSize(qreal width, qreal height);
    void setWidth(qreal width);
    void setHight(qreal height);


private:
    LReportPrintSettingsPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(LReportPrintSettings)
};

LEAF_END_NAMESPACE

#endif // LREPORTPRINTSETTINGS_H
