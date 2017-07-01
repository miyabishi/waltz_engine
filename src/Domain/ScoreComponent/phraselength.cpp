#include "phraselength.h"

using namespace waltz::engine::ScoreComponent;

PhraseLength::PhraseLength(const MilliSeconds& aMilliSeconds)
    : mMilliSeconds_(aMilliSeconds)
{
}

PhraseLength::PhraseLength(const PhraseLength& aOther)
    : mMilliSeconds_(aOther.mMilliSeconds_)
{

}
PhraseLength& PhraseLength::operator=(const PhraseLength& aOther)
{
    mMilliSeconds_ = aOther.mMilliSeconds_;
    return (*this);
}

MilliSeconds PhraseLength::toMilliSeconds() const
{
    return mMilliSeconds_;
}
