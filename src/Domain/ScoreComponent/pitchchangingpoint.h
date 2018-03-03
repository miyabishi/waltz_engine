#ifndef PITCHPOINT_H
#define PITCHPOINT_H

#include <QSharedPointer>
#include <waltz_common/parameters.h>
#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class PitchChangingPoint
            {
            public:
                explicit PitchChangingPoint(const common::Commands::Parameters& aParameters);
            public:
                MilliSeconds position() const;
                double value() const;

            private:
                MilliSeconds mPosition_;
                double mValue_;

            private:
                PitchChangingPoint(const PitchChangingPoint& aOther);
                PitchChangingPoint& operator=(const PitchChangingPoint& aOther);
            };
            typedef QSharedPointer<PitchChangingPoint> PitchChangingPointPointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PITCHPOINT_H
