#include "vibrato.h"

using namespace waltz::engine::ScoreComponent;


Vibrato::Vibrato(VibratoLengthPointer aLength,
                 VibratoWavelengthPointer aWavelength,
                 VibratoAmplitudePointer aAmplitude)
 : mLength_(aLength)
 , mWavelength_(aWavelength)
 , mAmplitude_(aAmplitude)
{
}


double Vibrato::calculatePitch(double aValue, MilliSeconds aPosition)
{
    // 音階の公比は 12√2 なので　2√2^(波形)で行けるはず

    return aValue;
}
