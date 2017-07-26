#include "pitchchangingpoint.h"

using namespace waltz::engine::ScoreComponent;

PitchChangingPoint::PitchChangingPoint(const double& aValue)
    : mValue_(aValue)
{
}

double PitchChangingPoint::value() const
{
    return mValue_;
}
