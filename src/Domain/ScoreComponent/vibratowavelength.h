#ifndef VIBRATOWAVELENGTH_H
#define VIBRATOWAVELENGTH_H

#include <QSharedPointer>
#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class VibratoWavelength
            {
            public:
                explicit VibratoWavelength(const MilliSeconds aMilliSeconds);
                MilliSeconds divide(const MilliSeconds aValue) const;

            private:
                MilliSeconds mMilliSeconds_;

            private:
                VibratoWavelength(const VibratoWavelength& aOther);
                VibratoWavelength& operator=(const VibratoWavelength& aOther);
            };
            typedef QSharedPointer<VibratoWavelength> VibratoWavelengthPointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // VIBRATOWAVELENGTH_H
