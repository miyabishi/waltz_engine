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
                TONE_C = -9,
                TONE_C_Sharp = -8,
                TONE_D = -7,
                TONE_D_Sharp = -6,
                TONE_E = -5,
                TONE_F = -4,
                TONE_F_Sharp = -3,
                TONE_G = -2,
                TONE_G_Sharp = -1,
                TONE_A = 0,
                TONE_A_Sharp = 1,
                TONE_B = 2
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
                ToneValue mValue_;
                Octave    mOctave_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // TONE_H
