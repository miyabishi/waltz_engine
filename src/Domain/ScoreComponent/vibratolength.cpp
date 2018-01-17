#include "vibratolength.h"

using namespace waltz::engine::ScoreComponent;

VibratoLength::VibratoLength(const MilliSeconds aMilliSeconds)
    : mValue_(aMilliSeconds)
{
}


MilliSeconds VibratoLength::value() const
{
    return mValue_;
}
