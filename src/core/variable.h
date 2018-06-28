#ifndef VARIABLE_H
#define VARIABLE_H

#include "qtreportglobal.h"
#include "seriazbleobject.h"

LEAF_BEGIN_NAMESPACE

class Variable : public SeriazbleObject
{
    Q_OBJECT

    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

public:

    enum Type {
        PrintDate,
        PrintYear,
        PrintMonth,
        PrintDay,

        PrintTime,
        PrintHour,
        PrintMinute,
        PrintSecond
    };
    Q_ENUM(Type)

    Variable(Type type, QObject *parent = nullptr);

    Type type() const;
    QVariant value() const;

public Q_SLOTS:
    void setType(Type type);

Q_SIGNALS:
    void typeChanged(Type type);

private:
    Type m_type;
};

LEAF_END_NAMESPACE

#endif // VARIABLE_H
