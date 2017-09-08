#ifndef SCORE_H
#define SCORE_H

#include <QList>
#include <QByteArray>
#include <QSharedPointer>
#include <waltz_common/parameters.h>
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
                explicit Score(const waltz::common::Commands::Parameters& aParameters);
                Score(const Score& aOther);
                Score& operator=(const Score& aOther);
                waltz::engine::SoundPlayer::SoundDataPointer toSoundData() const;

            private:
                Phrases mPhrases_;
            };
            typedef QSharedPointer<Score> ScorePointer;
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // SCORE_H
