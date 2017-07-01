#ifndef PHRASE_H
#define PHRASE_H

#include <iphrase.h>
#include <QVector>
#include <vector>
#include <QByteArray>
#include "notes.h"
#include "phraselength.h"
#include "phrasestarttime.h"
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
                waltz::engine::SoundPlayer::SoundData toSoundData() const;
                PhraseStartTime phraseStartTime() const;
                PhraseLength    phraseLength() const;
                MilliSeconds    endTime() const;

            private:
                Notes           mNotes_;

            };
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // PHRASE_H
