#ifndef PHRASESTARTTIME_H
#define PHRASESTARTTIME_H

#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class PhraseStartTime
            {
            public:
                explicit PhraseStartTime(const MilliSeconds& aPhraseStartTime);
                PhraseStartTime(const PhraseStartTime& aOther);
                PhraseStartTime& operator=(const PhraseStartTime& aOther);
            public:
                MilliSeconds toMilliSeconds() const;

            private:
                MilliSeconds mPhraseStartTime_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PHRASESTARTTIME_H
