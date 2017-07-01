#include <QDebug>
#include "score.h"

using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;

Score::Score(const Phrases& aPhrases)
    :mPhrases_(aPhrases)
{
}
Score::Score(const Score& aOther)
    :mPhrases_(aOther.mPhrases_)
{
}

Score& Score::operator=(const Score& aOther)
{
    mPhrases_ = aOther.mPhrases_;
    return (*this);
}

SoundData Score::toSoundData() const
{
    return mPhrases_.toSoundData();
}

