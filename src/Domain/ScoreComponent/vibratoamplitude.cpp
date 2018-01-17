#include "vibratoamplitude.h"

using namespace waltz::engine::ScoreComponent;

VibratoAmplitude::VibratoAmplitude(const double aValue)
    : mValue_(aValue)
{
}

double VibratoAmplitude::multipliedBy(double aValue)
{
    return mValue_ * aValue;
}
