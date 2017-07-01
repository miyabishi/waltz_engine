#include "phrasestarttime.h"

using namespace waltz::engine::ScoreComponent;

PhraseStartTime::PhraseStartTime(const MilliSeconds& aPhraseStartTime)
    : mPhraseStartTime_(aPhraseStartTime)
{

}

PhraseStartTime::PhraseStartTime(const PhraseStartTime &aOther)
    : mPhraseStartTime_(aOther.mPhraseStartTime_)
{
}

PhraseStartTime& PhraseStartTime::operator=(const PhraseStartTime &aOther)
{
    mPhraseStartTime_ = aOther.mPhraseStartTime_;
    return (*this);
}

MilliSeconds PhraseStartTime::toMilliSeconds() const
{
    return mPhraseStartTime_;
}
