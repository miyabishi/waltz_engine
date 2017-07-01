#include <QMap>
#include "tone.h"

using namespace waltz::engine::ScoreComponent;

Tone::Tone(const ToneValue& aValue,
           const Octave& aOctave)
    : mValue_(aValue)
    , mOctave_(aOctave)
{
}

Tone::Tone(const Tone &aOther)
    : mValue_(aOther.mValue_)
    , mOctave_(aOther.mOctave_)
{
}

Tone& Tone::operator=(const Tone &aOther)
{
    mValue_ = aOther.mValue_;
    mOctave_ = aOther.mOctave_;
    return (*this);
}

double Tone::frequency() const
{
    return mOctave_.multiplyOctave(baseFrequency());
}

double Tone::baseFrequency() const
{
    QMap<ToneValue, double> frequencyMap;
    frequencyMap[TONE_C]       = 32.703;
    frequencyMap[TONE_C_Sharp] = 34.648;
    frequencyMap[TONE_D]       = 36.708;
    frequencyMap[TONE_D_Sharp] = 38.891;
    frequencyMap[TONE_E]       = 41.203;
    frequencyMap[TONE_F]       = 43.645;
    frequencyMap[TONE_F_Sharp] = 46.249;
    frequencyMap[TONE_G]       = 48.999;
    frequencyMap[TONE_G_Sharp] = 51.913;
    frequencyMap[TONE_A]       = 55.000;
    frequencyMap[TONE_A_Sharp] = 58.270;
    frequencyMap[TONE_B]       = 61.735;

    return frequencyMap[mValue_];
}
