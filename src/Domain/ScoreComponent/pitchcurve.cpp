#include "pitchcurve.h"

using namespace waltz::engine::ScoreComponent;



PitchCurve::PitchCurve()
{

}

void PitchCurve::append(const PitchChangingPointPointer& aPitchChangingPoint)
{
    mPitchCurve_.append(aPitchChangingPoint);
}

double PitchCurve::calculateValue(int aIndex, int aLength)
{
    return mPitchCurve_.at(((mPitchCurve_.length() - 1) * aIndex) / aLength)->value();
}

int PitchCurve::length() const
{
    return mPitchCurve_.length();
}
