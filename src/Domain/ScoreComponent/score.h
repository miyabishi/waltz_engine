#ifndef SCORE_H
#define SCORE_H

#include <QList>
#include <QByteArray>
#include "phrases.h"
#include "src/Domain/SoundPlayer/sounddata.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Score
            {
            public:
                explicit Score(const Phrases& aPhrases);
                Score(const Score& aOther);
                Score& operator=(const Score& aOther);
                waltz::engine::SoundPlayer::SoundData toSoundData() const;

            private:
                Phrases mPhrases_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // SCORE_H
