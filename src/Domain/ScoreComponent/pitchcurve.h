#ifndef PITCHCURVE_H
#define PITCHCURVE_H

#include <memory>
#include <QSharedPointer>

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
            private:
                PitchCurve& operator =(const PitchCurve& aOther);
                PitchCurve(const PitchCurve& aOther);
            };
            typedef QSharedPointer<PitchCurve>(PitchCurvePointer);

        } // namespace SoundComponent
    } // namespace engine
} // namespace waltz

#endif // PITCHCURVE_H
