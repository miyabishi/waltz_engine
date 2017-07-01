#ifndef TONE_H
#define TONE_H

#include "octave.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            enum ToneValue
            {
                TONE_C = 0,
                TONE_C_Sharp = 1,
                TONE_D = 2,
                TONE_D_Sharp = 3,
                TONE_E = 4,
                TONE_F = 5,
                TONE_F_Sharp = 6,
                TONE_G = 7,
                TONE_G_Sharp = 8,
                TONE_A = 9,
                TONE_A_Sharp = 10,
                TONE_B = 11
            };

            class Tone
            {
            public:
                explicit Tone(const ToneValue& aToneValue,
                              const Octave& aOctave);
                Tone(const Tone& aOther);
                Tone& operator=(const Tone& aOther);

            public:
                double frequency() const;
            private:
                double baseFrequency() const;

            private:
                ToneValue mValue_;
                Octave    mOctave_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // TONE_H
