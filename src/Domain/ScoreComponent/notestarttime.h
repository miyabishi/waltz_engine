#ifndef NOTESTARTTIME_H
#define NOTESTARTTIME_H

#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class NoteStartTime
            {
            public:
                explicit NoteStartTime(const MilliSeconds& aMilliSecond);
                NoteStartTime(const NoteStartTime& aOther);
                NoteStartTime& operator=(const NoteStartTime& aOther);
            public:
                MilliSeconds toMilliSeconds() const;

            private:
                MilliSeconds mMilliSecond_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // NOTESTARTTIME_H
