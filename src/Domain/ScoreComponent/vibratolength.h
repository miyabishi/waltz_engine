#ifndef VIBRATOLENGTH_H
#define VIBRATOLENGTH_H

#include <QSharedPointer>
#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class VibratoLength
            {
            public:
                explicit VibratoLength(const MilliSeconds aMilliSeconds);

            private:
                MilliSeconds mValue_;

            private:
                VibratoLength(const VibratoLength& aOther);
                VibratoLength& operator=(const VibratoLength& aOther);
            };
            typedef QSharedPointer<VibratoLength> VibratoLengthPointer;
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // VIBRATOLENGTH_H
