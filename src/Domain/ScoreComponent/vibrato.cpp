#include <qmath.h>
#include "vibrato.h"
#include "timerange.h"

using namespace waltz::engine::ScoreComponent;


Vibrato::Vibrato(VibratoStartTimePointer aStartTime,
                 VibratoLengthPointer aLength,
                 VibratoWavelengthPointer aWavelength,
                 VibratoAmplitudePointer aAmplitude)
 : mStartTime_(aStartTime)
 , mLength_(aLength)
 , mWavelength_(aWavelength)
 , mAmplitude_(aAmplitude)
{
}

double Vibrato::calculatePitch(double aValue,const MilliSeconds& aPosition)
{
    TimeRange timeRange = mStartTime_->timeRangeTo(mLength_);
    if (! timeRange.within(aPosition)) return aValue;

    // 音階の公比は 12√2 なので　2√2^(波形)で行けるはず
    double wave = mAmplitude_->multipliedBy(
                qSin(
                    mWavelength_->divide(
                         mStartTime_->subtractVibratoStartTimeFrom(
                            aPosition)
                         ).value()
                    * 2 * M_PI));

    return aValue * qPow(2, wave/12.0);
}
