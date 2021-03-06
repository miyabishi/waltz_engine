#ifndef PHRASES_H
#define PHRASES_H

#include <QList>
#include <QByteArray>
#include "src/Domain/SoundPlayer/sounddata.h"
#include "phrase.h"
#include "milliseconds.h"
#include "pitchcurve.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Phrases
            {
            public:
                Phrases();
                Phrases(const Phrases& aOther);
                Phrases& operator=(const Phrases& aOther);
                void apend(const PhrasePointer& aPhrase);

            public:
                waltz::engine::SoundPlayer::SoundDataPointer toSoundData(
                        const PitchCurvePointer aPitchCurve) const;
                MilliSeconds length() const;

            private:
                QList<PhrasePointer> mPhrases_;
            };
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PHRASES_H
