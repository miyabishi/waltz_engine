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

