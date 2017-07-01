#include "parameters.h"

using namespace waltz::engine::Commands;

Parameters::Parameters()
    :mParameters_()
{
}

Parameters::Parameters(const Parameters &aOther)
    :mParameters_(aOther.mParameters_)
{
}

Parameters& Parameters::operator =(const Parameters& aOther)
{
    mParameters_ = aOther.mParameters_;
    return (*this);
}

Parameter Parameters::find(const QString& aParameterName) const
{
    return mParameters_.value(aParameterName, Parameter("",QVariant()));
}

void Parameters::append(const Parameter &aParameter)
{
    mParameters_[aParameter.name()] = aParameter;
}

QJsonArray Parameters::toJsonArray() const
{
    QJsonArray jsonArray;

    foreach(const Parameter& parameter, mParameters_)
    {
        jsonArray.append(parameter.toJsonValue());
    }
    return jsonArray;
}

