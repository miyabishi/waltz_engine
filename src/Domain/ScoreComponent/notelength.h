#ifndef NOTELENGTH_H
#define NOTELENGTH_H

#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class NoteLength
            {
            public:
                explicit NoteLength(const MilliSeconds& aMilliSecond_);
                NoteLength(const NoteLength& aOther);
                NoteLength& operator=(const NoteLength& aOther);

            public:
                MilliSeconds toMilliSeconds() const;

            private:
                MilliSeconds mMilliSecond_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // NOTELENGTH_H
