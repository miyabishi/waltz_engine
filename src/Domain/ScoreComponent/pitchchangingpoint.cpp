#include "pitchchangingpoint.h"

using namespace waltz::engine::ScoreComponent;

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
