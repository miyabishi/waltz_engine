#ifndef PHRASELENGTH_H
#define PHRASELENGTH_H

#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class PhraseLength
            {
            public:
                explicit PhraseLength(const MilliSeconds& aMilliSeconds);
                PhraseLength(const PhraseLength& aOther);
                PhraseLength& operator=(const PhraseLength& aOther);
            public:
                MilliSeconds toMilliSeconds() const;

            private:
                MilliSeconds mMilliSeconds_;
            };
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PHRASELENGTH_H
