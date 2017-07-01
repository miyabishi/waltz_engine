#include <QDebug>
#include "phrases.h"


using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;

Phrases::Phrases()
{
}

Phrases::Phrases(const Phrases &aOther)
    :mPhrases_(aOther.mPhrases_)
{
}

Phrases& Phrases::operator=(const Phrases& aOther)
{
    mPhrases_ = aOther.mPhrases_;
    return (*this);
}

void Phrases::apend(const Phrase &aPhrase)
{
    mPhrases_.append(aPhrase);
}

SoundData Phrases::toSoundData() const
{

    SoundData soundData;
    for(int index = 0; index < mPhrases_.length(); ++index)
    {
        soundData.appendData(mPhrases_.at(index).toSoundData(),
                             mPhrases_.at(index).phraseStartTime().toMilliSeconds());
    }
    return soundData;
}

MilliSeconds Phrases::length() const
{
    if (mPhrases_.isEmpty())
    {
        return MilliSeconds();
    }
    return mPhrases_.last().endTime();
}
