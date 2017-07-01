#include "samplesize.h"

using namespace waltz::engine::SoundPlayer;

SampleSize::SampleSize()
    : mSampleSize_(-1)
{
}

SampleSize::SampleSize(const int aSampleSize)
    :mSampleSize_ (aSampleSize)
{
}

SampleSize::SampleSize(const SampleSize &aOther)
    :mSampleSize_(aOther.mSampleSize_)
{
}

SampleSize& SampleSize::operator=(const SampleSize &aOther)
{
    mSampleSize_ = aOther.mSampleSize_;
    return (*this);
}

int SampleSize::value() const
{
    return mSampleSize_;
}

QAudioFormat::SampleType SampleSize::sampleType() const
{
    if (mSampleSize_ == 8)
    {
        return QAudioFormat::UnSignedInt;
    }
    return QAudioFormat::SignedInt;
}

bool SampleSize::isInitialized() const
{
    return mSampleSize_ > 0;
}

