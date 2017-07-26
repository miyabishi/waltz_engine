#ifndef PITCHPOINT_H
#define PITCHPOINT_H

#include <QSharedPointer>

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class PitchChangingPoint
            {
            public:
                PitchChangingPoint(const double& aValue);

                double value() const;

            private:
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
