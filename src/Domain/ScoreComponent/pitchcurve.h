#ifndef PITCHCURVE_H
#define PITCHCURVE_H

#include <memory>
#include <QSharedPointer>
#include <QList>
#include "pitchchangingpoint.h"
#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class PitchCurve
            {
            public:
                PitchCurve();
                void append(const PitchChangingPointPointer& aPitchChangingPoint);
                int length() const;
                double calculateValue(const MilliSeconds& aPosition);

            private:
                QList<PitchChangingPointPointer> mPitchCurve_;

            private:
                PitchCurve& operator =(const PitchCurve& aOther);
                PitchCurve(const PitchCurve& aOther);
            };
            typedef QSharedPointer<PitchCurve>(PitchCurvePointer);

        } // namespace SoundComponent
    } // namespace engine
} // namespace waltz

#endif // PITCHCURVE_H
