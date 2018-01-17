#include "milliseconds.h"
#include "src/Settings/enginesettings.h"

using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::Settings;

MilliSeconds::MilliSeconds()
    : mMilliSeconds_(0)
{
}

MilliSeconds::MilliSeconds(const double aMilliSeconds)
    : mMilliSeconds_(aMilliSeconds)
{
}

MilliSeconds::MilliSeconds(const MilliSeconds &aOther)
    : mMilliSeconds_(aOther.mMilliSeconds_)
{
}

MilliSeconds MilliSeconds::fromSeconds(const double aSeconds)
{
    return MilliSeconds(aSeconds * 1000.0);
}

MilliSeconds& MilliSeconds::operator=(const MilliSeconds &aOther)
{
    mMilliSeconds_ = aOther.mMilliSeconds_;
    return (*this);
}

double MilliSeconds::value() const
{
    return mMilliSeconds_;
}
double MilliSeconds::toSeconds() const
{
    return mMilliSeconds_ / 1000.0;
}

int MilliSeconds::toArrayLength(const waltz::engine::SoundPlayer::SampleRate& aSampleRate) const
{
    return toSeconds() * aSampleRate.value();
}

int MilliSeconds::toBitPosition(const waltz::engine::SoundPlayer::SampleRate& aSampleRate,
                                const waltz::engine::SoundPlayer::SampleSize& aSampleSize) const
{
    return toArrayLength(aSampleRate.value()) * aSampleSize.value() / 8;
}

int MilliSeconds::toF0ArrayLength() const
{
    return (int)(mMilliSeconds_ / EngineSettings::getInstance().framePeriod());
}

MilliSeconds MilliSeconds::add(const MilliSeconds &aOther) const
{
    return MilliSeconds(value() + aOther.value());
}

MilliSeconds MilliSeconds::subtract(const MilliSeconds &aOther) const
{
    return MilliSeconds(value() - aOther.value());
}

MilliSeconds MilliSeconds::dividedBy(const MilliSeconds& aValue) const
{
    return MilliSeconds(value() / aValue.value());
}
