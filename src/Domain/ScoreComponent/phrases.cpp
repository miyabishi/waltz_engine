#include "phrases.h"
#include <QDebug>

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

void Phrases::apend(const PhrasePointer &aPhrase)
{
    mPhrases_.append(aPhrase);
}

SoundDataPointer Phrases::toSoundData(const PitchCurvePointer aPitchCurve) const
{
    SoundDataPointer soundData(new SoundData());
    for(int index = 0; index < mPhrases_.length(); ++index)
    {
        qDebug() << "phrase index:" << index;
        soundData = mPhrases_.at(index)->appendPhraseSoundData(soundData, aPitchCurve);
    }

    return soundData;
}

MilliSeconds Phrases::length() const
{
    if (mPhrases_.isEmpty())
    {
        return MilliSeconds();
    }
    return mPhrases_.last()->endTime();
}
