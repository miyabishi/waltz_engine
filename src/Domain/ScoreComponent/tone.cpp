#include <qmath.h>
#include <QMap>
#include "tone.h"

using namespace waltz::engine::ScoreComponent;

namespace
{
    const double BASE_PITCH_A = 440.0;
}

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
    return BASE_PITCH_A * qPow(2,double((int)(mValue_) + (mOctave_.value() - 7) * 12 ) /12.0);
}
