#ifndef VIBRATOSTARTTIME_H
#define VIBRATOSTARTTIME_H

#include <QSharedPointer>
#include "milliseconds.h"
#include "timerange.h"
#include "vibratolength.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class VibratoStartTime
            {
            public:
                explicit VibratoStartTime(MilliSeconds aValue);
                MilliSeconds subtractVibratoStartTimeFrom(const MilliSeconds) const;
                TimeRange timeRangeTo(const VibratoLengthPointer aLength) const;

            private:
                MilliSeconds mValue_;
            };
            typedef QSharedPointer<VibratoStartTime> VibratoStartTimePointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // VIBRATOSTARTTIME_H
