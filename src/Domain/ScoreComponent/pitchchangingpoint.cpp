#include "pitchchangingpoint.h"

using namespace waltz::engine::ScoreComponent;

namespace
{
    const QString PARAMETER_NAME_PITCH_CHANGING_POINT_TIME = "Time";
    const QString PARAMETER_NAME_PITCH_CHANGING_POINT_FREQUENCY = "Frequency";
}

PitchChangingPoint::PitchChangingPoint(const common::Commands::Parameters &aParameters)
    : mPosition_(MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_PITCH_CHANGING_POINT_TIME).value().toDouble()))
    , mValue_(aParameters.find(PARAMETER_NAME_PITCH_CHANGING_POINT_FREQUENCY).value().toDouble())
{
}

PitchChangingPoint::PitchChangingPoint(const MilliSeconds& aPosition,
                                       const double& aValue)
    : mPosition_(aPosition)
    , mValue_(aValue)
{
}

MilliSeconds PitchChangingPoint::position() const
{
    return mPosition_;
}

double PitchChangingPoint::value() const
{
    return mValue_;
}
