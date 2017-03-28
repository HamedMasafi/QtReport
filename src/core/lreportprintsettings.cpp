#include "lreportprintsettings.h"

#include <QSizeF>

LEAF_BEGIN_NAMESPACE

class LReportPrintSettingsPrivate
{
public:
    LReportPrintSettingsPrivate(LReportPrintSettings *parent) : q_ptr(parent)
    {

    }

    qreal marginLeft;
    qreal marginBottom;
    qreal marginTop;
    qreal marginRight;

    QSizeF pageSize;

    QString filePath;


private :
    LReportPrintSettings  *q_ptr;
    Q_DECLARE_PUBLIC(LReportPrintSettings)
};

LReportPrintSettings::LReportPrintSettings() : QObject(), d_ptr(new LReportPrintSettingsPrivate(this))
{

}


qreal LReportPrintSettings::marginLeft() const
{
    Q_D(const LReportPrintSettings);
    return d->marginLeft;
}
qreal LReportPrintSettings::marginBottom() const
{
    Q_D(const LReportPrintSettings);
    return d->marginBottom;
}
qreal LReportPrintSettings::marginTop() const
{
    Q_D(const LReportPrintSettings);
    return d->marginTop;
}
qreal LReportPrintSettings::marginRight() const
{
    Q_D(const LReportPrintSettings);
    return d->marginRight;
}


void LReportPrintSettings::setMarginLeft(qreal value)
{
    Q_D(LReportPrintSettings);
    d->marginLeft = value;
}
void LReportPrintSettings::setMarginRight(qreal value)
{
    Q_D(LReportPrintSettings);
    d->marginRight = value;
}
void LReportPrintSettings::setMarginTop(qreal value)
{
    Q_D(LReportPrintSettings);
    d->marginTop = value;
}
void LReportPrintSettings::setMarginBottom(qreal value)
{
    Q_D(LReportPrintSettings);
    d->marginBottom = value;
}

void LReportPrintSettings::setMargins(qreal marginLeft, qreal marginTop,
                         qreal marginRight, qreal marginBottom )
{
    Q_D(LReportPrintSettings);
    d->marginLeft    = marginLeft;
    d->marginBottom  = marginBottom;
    d->marginTop     = marginTop;
    d->marginRight   = marginRight;
}

QSizeF LReportPrintSettings::designArea() const
{
    return QSizeF(pageSize().width() - marginLeft() - marginRight(),
                  pageSize().height() - marginTop() - marginBottom());
}

QSizeF LReportPrintSettings::pageSize() const
{
    Q_D(const LReportPrintSettings);
    return d->pageSize;
}

void LReportPrintSettings::setSize( QSizeF s )
{
    Q_D(LReportPrintSettings);
    d->pageSize = s;
}

void LReportPrintSettings::setSize( qreal width, qreal height )
{
    Q_D(LReportPrintSettings);
    d->pageSize = QSizeF( width, height );
}

void LReportPrintSettings::setWidth( qreal width )
{
    Q_D(LReportPrintSettings);
    d->pageSize = QSizeF( width, d->pageSize.height() );
}

void LReportPrintSettings::setHight( qreal height )
{
    Q_D(LReportPrintSettings);
    d->pageSize = QSizeF( d->pageSize.width(), height );
}

LEAF_END_NAMESPACE
