#include "correspondencealias.h"

using namespace waltz::engine::VocalComponent;
using namespace waltz::common::Commands;

namespace
{
    const QString PARAMETER_NAME = "CorrenspondenceAlias";
}

CorrespondenceAlias::CorrespondenceAlias(const QString& aValue)
    :mValue_(aValue)
{
}

Parameters CorrespondenceAlias::toParameters() const
{
    Parameters parameters;
    parameters.append(Parameter(PARAMETER_NAME, mValue_));
    return parameters;
}
