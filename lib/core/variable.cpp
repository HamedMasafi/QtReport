#include <QtCore/QDateTime>
#include <QtCore/QMetaEnum>
#include <QtCore/QVariant>

#include "variable.h"

LEAF_BEGIN_NAMESPACE

Variable::Variable(Variable::Type type, QObject *parent) : SeriazbleObject(parent),
    m_type(type)
{

}

Variable::Type Variable::type() const
{
    return m_type;
}

QVariant Variable::value() const
{
    switch (m_type) {
    case PrintDate:       return QDate::currentDate();
    case PrintYear:       return QDate::currentDate().year();
    case PrintMonth:      return QDate::currentDate().month();
    case PrintDay:        return QDate::currentDate().day();
    case PrintTime:       return QTime::currentTime();
    case PrintHour:       return QTime::currentTime().hour();
    case PrintMinute:     return QTime::currentTime().minute();
    case PrintSecond:     return QTime::currentTime().second();
    }

    return QVariant();
}

void Variable::setType(Variable::Type type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

LEAF_END_NAMESPACE
