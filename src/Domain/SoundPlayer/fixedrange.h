#ifndef FIXEDRANGE_H
#define FIXEDRANGE_H

#include "src/Domain/ScoreComponent/milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class FixedRange
            {
            public:
                FixedRange();
            private:
                waltz::engine::ScoreComponent::MilliSeconds mLength_;
                waltz::engine::ScoreComponent::MilliSeconds mOverlap_;
                waltz::engine::ScoreComponent::MilliSeconds mPreceding_;
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // FIXEDRANGE_H
