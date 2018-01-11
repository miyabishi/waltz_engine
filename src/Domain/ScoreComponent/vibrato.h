#ifndef VIBRATO_H
#define VIBRATO_H

#include <QSharedPointer>
#include "vibratolength.h"
#include "vibratoamplitude.h"
#include "vibratowavelength.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Vibrato
            {
            public:
                // length wavelength amplitude
                Vibrato(VibratoLengthPointer aLength,
                        VibratoWavelengthPointer aWavelength,
                        VibratoAmplitudePointer aAmplitude);
            public:
                double calculatePitch(double aValue, MilliSeconds aPosition);

            private:
                VibratoLengthPointer mLength_;
                VibratoWavelengthPointer mWavelength_;
                VibratoAmplitudePointer mAmplitude_;

            private:
                Vibrato(const Vibrato& aOther);
                Vibrato& operator=(const Vibrato& aOther);
            };
            typedef QSharedPointer<Vibrato> VibratoPointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // VIBRATO_H
