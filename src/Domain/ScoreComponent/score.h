#ifndef SCORE_H
#define SCORE_H

#include <QList>
#include <QByteArray>
#include <QSharedPointer>

#include <waltz_common/parameters.h>
#include <waltz_common/parameterslist.h>

#include "src/Domain/SoundPlayer/sounddata.h"
#include "phrases.h"
#include "pitchcurve.h"

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
                explicit Score(const common::Commands::Parameters& aParameters);
                Score(const Score& aOther);
                Score& operator=(const Score& aOther);
                waltz::engine::SoundPlayer::SoundDataPointer toSoundData() const;

            private:
                void loadPhrases(const common::Commands::ParametersList& aParameterList);
                void loadPitchCurve(const common::Commands::ParametersList& aParameterList);

            private:
                Phrases mPhrases_;
                PitchCurvePointer mPitchCurve_;

            };
            typedef QSharedPointer<Score> ScorePointer;
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // SCORE_H
