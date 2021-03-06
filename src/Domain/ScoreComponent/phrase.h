#ifndef PHRASE_H
#define PHRASE_H

#include <iphrase.h>
#include <QVector>
#include <vector>
#include <QByteArray>
#include <QSharedPointer>
#include "notes.h"
#include "phraselength.h"
#include "phrasestarttime.h"
#include "pitchcurve.h"
#include "src/Domain/SoundPlayer/sounddata.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Alias;
            class Phrase : public waltz::agent::IPhrase
            {
            public:
                explicit Phrase(const Notes& aNotes);
                Phrase(const Phrase& aOther);
                Phrase& operator=(const Phrase& aOther);
                ~Phrase();

            public:
                std::vector<waltz::agent::IAlias*> aliases() const;
                waltz::engine::SoundPlayer::SoundDataPointer toSoundData(const PitchCurvePointer aPitchCurve);
                PhraseStartTime phraseStartTime() const;
                PhraseLength    phraseLength() const;
                waltz::engine::SoundPlayer::SoundDataPointer appendPhraseSoundData(
                        const waltz::engine::SoundPlayer::SoundDataPointer aSoundData,
                        const PitchCurvePointer aPitchCurve);


                MilliSeconds    endTime() const;

            private:
                Notes           mNotes_;
                MilliSeconds    mPrecedingTime_; // TODO 修正対象
                MilliSeconds    mOverlapTime_; // TODO 修正対象
            };
            typedef QSharedPointer<Phrase> PhrasePointer;
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PHRASE_H
