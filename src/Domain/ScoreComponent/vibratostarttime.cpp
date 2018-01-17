#include "vibratostarttime.h"

using namespace waltz::engine::ScoreComponent;

VibratoStartTime::VibratoStartTime(const MilliSeconds aValue)
    : mValue_(aValue)
{
}

MilliSeconds VibratoStartTime::subtractVibratoStartTimeFrom(const MilliSeconds aValue) const
{
    return aValue.subtract(mValue_);
}

TimeRange VibratoStartTime::timeRangeTo(const VibratoLengthPointer aLength) const
{
    return TimeRange(mValue_, mValue_.add(aLength->value()));
}
