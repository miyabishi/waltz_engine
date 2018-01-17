#include "timerange.h"

using namespace waltz::engine::ScoreComponent;

TimeRange::TimeRange(const MilliSeconds& aStartTime,
                     const MilliSeconds& aEndTime)
    : mStartTime_(aStartTime)
    , mEndTime_(aEndTime)
{
}

MilliSeconds TimeRange::startTime() const
{
    return mStartTime_;
}

MilliSeconds TimeRange::endTime() const
{
    return mEndTime_;
}

MilliSeconds TimeRange::length() const
{
    return mEndTime_.subtract(mStartTime_);
}

bool TimeRange::within(const MilliSeconds& aPosition) const
{
    return (startTime().value() < aPosition.value() && aPosition.value() < endTime().value());
}
