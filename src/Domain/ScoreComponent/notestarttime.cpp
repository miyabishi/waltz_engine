#include "notestarttime.h"

using namespace waltz::engine::ScoreComponent;

NoteStartTime::NoteStartTime(const MilliSeconds& aMilliSecond)
    :mMilliSecond_(aMilliSecond)
{

}

NoteStartTime::NoteStartTime(const NoteStartTime &aOther)
    :mMilliSecond_(aOther.mMilliSecond_)
{
}

NoteStartTime& NoteStartTime::operator=(const NoteStartTime &aOther)
{
    mMilliSecond_ = aOther.mMilliSecond_;
    return (*this);
}

MilliSeconds NoteStartTime::toMilliSeconds() const
{
    return mMilliSecond_;
}
