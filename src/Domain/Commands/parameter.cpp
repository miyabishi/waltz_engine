#include <QJsonObject>
#include "parameter.h"

using namespace waltz::engine::Commands;

Parameter::Parameter()
{
}

Parameter::Parameter(const QString& aName,
                     const QVariant& aValue)
    : mName_(aName)
    , mValue_(aValue)
{
}

Parameter::Parameter(const Parameter &aOther)
    : mName_(aOther.mName_)
    , mValue_(aOther.mValue_)
{
}

Parameter& Parameter::operator=(const Parameter &aOther)
{
    mValue_ = aOther.mValue_;
    mName_ = aOther.mName_;
    return (*this);
}

QJsonValue Parameter::toJsonValue() const
{
    QJsonValue value;
    switch(mValue_.type())
    {
    case QVariant::String:
        value = mValue_.toString();
        break;
    case QVariant::Int:
        value = mValue_.toInt();
        break;
    case QVariant::Double:
        value = mValue_.toDouble();
        break;
    default:
        break;
    }

    QJsonObject jsonObject;
    jsonObject[PARAMETER_KEY_NAME]  = mName_;
    jsonObject[PARAMETER_KEY_VALUE] = value;
    return QJsonValue(jsonObject);
}
QString Parameter::name() const
{
    return mName_;
}


QString Parameter::toString() const
{
    return mValue_.toString();
}

int Parameter::toInt() const
{
    return mValue_.toInt();
}

double Parameter::toDouble() const
{
    return mValue_.toDouble();
}
