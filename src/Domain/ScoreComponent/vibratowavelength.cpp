#include "vibratowavelength.h"

using namespace waltz::engine::ScoreComponent;

VibratoWavelength::VibratoWavelength(const MilliSeconds aMilliSeconds)
    :mMilliSeconds_(aMilliSeconds)
{

}

MilliSeconds VibratoWavelength::divide(const MilliSeconds aValue) const
{
    return aValue.dividedBy(mMilliSeconds_);
}


