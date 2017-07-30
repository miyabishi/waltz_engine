#include "octave.h"

using namespace waltz::engine::ScoreComponent;

Octave::Octave(const int aValue)
    : mValue_(aValue)
{
}

Octave::Octave(const Octave& aOther)
    : mValue_(aOther.mValue_)
{
}

Octave& Octave::operator=(const Octave& aOther)
{
    mValue_ = aOther.mValue_;
    return (* this);
}

double Octave::multiplyOctave(double aBaseFrequency) const
{
    return aBaseFrequency * mValue_;
}

int Octave::value() const
{
    return mValue_;
}
