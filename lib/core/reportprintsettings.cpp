#include "core/reportprintsettings.h"

#include <QSizeF>

LEAF_BEGIN_NAMESPACE

class PrintSettingsPrivate
{
public:
    PrintSettingsPrivate(PrintSettings *parent) : q_ptr(parent)
    {

    }

    qreal marginLeft;
    qreal marginBottom;
    qreal marginTop;
    qreal marginRight;

    QSizeF pageSize;

    QString filePath;


private :
    PrintSettings  *q_ptr;
    Q_DECLARE_PUBLIC(PrintSettings)
};

PrintSettings::PrintSettings() : QObject(), d_ptr(new PrintSettingsPrivate(this))
{

}


qreal PrintSettings::marginLeft() const
{
    Q_D(const PrintSettings);
    return d->marginLeft;
}
qreal PrintSettings::marginBottom() const
{
    Q_D(const PrintSettings);
    return d->marginBottom;
}
qreal PrintSettings::marginTop() const
{
    Q_D(const PrintSettings);
    return d->marginTop;
}
qreal PrintSettings::marginRight() const
{
    Q_D(const PrintSettings);
    return d->marginRight;
}


void PrintSettings::setMarginLeft(qreal value)
{
    Q_D(PrintSettings);
    d->marginLeft = value;
}
void PrintSettings::setMarginRight(qreal value)
{
    Q_D(PrintSettings);
    d->marginRight = value;
}
void PrintSettings::setMarginTop(qreal value)
{
    Q_D(PrintSettings);
    d->marginTop = value;
}
void PrintSettings::setMarginBottom(qreal value)
{
    Q_D(PrintSettings);
    d->marginBottom = value;
}

void PrintSettings::setMargins(qreal marginLeft, qreal marginTop,
                         qreal marginRight, qreal marginBottom )
{
    Q_D(PrintSettings);
    d->marginLeft    = marginLeft;
    d->marginBottom  = marginBottom;
    d->marginTop     = marginTop;
    d->marginRight   = marginRight;
}

QSizeF PrintSettings::designArea() const
{
    return QSizeF(pageSize().width() - marginLeft() - marginRight(),
                  pageSize().height() - marginTop() - marginBottom());
}

QSizeF PrintSettings::pageSize() const
{
    Q_D(const PrintSettings);
    return d->pageSize;
}

void PrintSettings::setSize( QSizeF s )
{
    Q_D(PrintSettings);
    d->pageSize = s;
}

void PrintSettings::setSize( qreal width, qreal height )
{
    Q_D(PrintSettings);
    d->pageSize = QSizeF( width, height );
}

void PrintSettings::setWidth( qreal width )
{
    Q_D(PrintSettings);
    d->pageSize = QSizeF( width, d->pageSize.height() );
}

void PrintSettings::setHight( qreal height )
{
    Q_D(PrintSettings);
    d->pageSize = QSizeF( d->pageSize.width(), height );
}

LEAF_END_NAMESPACE
