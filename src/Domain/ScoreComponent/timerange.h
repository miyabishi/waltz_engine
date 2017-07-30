#ifndef TIMERANGE_H
#define TIMERANGE_H

#include "src/Domain/ScoreComponent/milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class TimeRange
            {
            public:
                TimeRange(const MilliSeconds& aStartTime,
                          const MilliSeconds& aEndTime);
                MilliSeconds startTime() const;
                MilliSeconds endTime() const;
                MilliSeconds length() const;

            private:
                MilliSeconds mStartTime_;
                MilliSeconds mEndTime_;
            };

        } // namespace SoundComponent
    } // namespace engine
} // namespace waltz

#endif // TIMERANGE_H
