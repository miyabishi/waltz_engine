#ifndef VIBRATOAMPLITUDE_H
#define VIBRATOAMPLITUDE_H

#include <QSharedPointer>

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class VibratoAmplitude
            {
            public:
                explicit VibratoAmplitude(const double aValue);
                double multipliedBy(double aValue);

            private:
                double mValue_;

            private:
                VibratoAmplitude(const VibratoAmplitude& aOther);
                VibratoAmplitude& operator=(const VibratoAmplitude& aOther);
            };
            typedef QSharedPointer<VibratoAmplitude> VibratoAmplitudePointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // VIBRATOAMPLITUDE_H
