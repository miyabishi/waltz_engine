#include "samplerate.h"

using namespace waltz::engine::SoundPlayer;

SampleRate::SampleRate()
    :mSampleRate_(-1)
{
}

SampleRate::SampleRate(const int aSampleRate)
    :mSampleRate_(aSampleRate)
{
}


SampleRate::SampleRate(const SampleRate &aOther)
    :mSampleRate_(aOther.mSampleRate_)
{
}

SampleRate& SampleRate::operator=(const SampleRate &aOther)
{
    mSampleRate_ = aOther.mSampleRate_;
    return (*this);
}

int SampleRate::value() const
{
    return mSampleRate_;
}

bool SampleRate::isInitialized() const
{
    return mSampleRate_ > 0;
}
