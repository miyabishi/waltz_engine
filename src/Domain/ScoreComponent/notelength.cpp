#include "notelength.h"

using namespace waltz::engine::ScoreComponent;

NoteLength::NoteLength(const MilliSeconds& aMilliSecond)
    :mMilliSecond_(aMilliSecond)
{

}

NoteLength::NoteLength(const NoteLength& aOther)
    :mMilliSecond_(aOther.mMilliSecond_)
{
}

NoteLength& NoteLength::operator=(const NoteLength& aOther)
{
    mMilliSecond_ = aOther.mMilliSecond_;
    return (* this);
}

MilliSeconds NoteLength::toMilliSeconds() const
{
    return mMilliSecond_;
}
