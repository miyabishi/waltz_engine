#include "note.h"

using namespace waltz::engine::ScoreComponent;

Note::Note(const Tone& aTone,
           const Alias& aAlias,
           const NoteStartTime& aNoteStartTime,
           const NoteLength& aNoteLength)
    : mTone_(aTone)
    , mAlias_(*(new Alias(aAlias)))
    , mNoteStartTime_(aNoteStartTime)
    , mNoteLength_(aNoteLength)

{
}

Note::Note(const Note& aOther)
    : mTone_(aOther.mTone_)
    , mAlias_(aOther.mAlias_)
    , mNoteStartTime_(aOther.mNoteStartTime_)
    , mNoteLength_(aOther.mNoteLength_)
{

}

Note& Note::operator=(const Note& aOther)
{
    mTone_ = aOther.mTone_;
    mAlias_ = aOther.mAlias_;
    mNoteStartTime_ = aOther.mNoteStartTime_;
    mNoteLength_ = aOther.mNoteLength_;

    return (* this);
}

Note::~Note()
{
    delete &mAlias_;
}
Alias* Note::alias() const
{
    return &mAlias_;
}

NoteLength Note::noteLength() const
{
    return mNoteLength_;
}

NoteStartTime Note::noteStartTime() const
{
    return mNoteStartTime_;
}

MilliSeconds Note::endTime() const
{
    double endTime;
    endTime = mNoteStartTime_.toMilliSeconds().value()
              + mNoteLength_.toMilliSeconds().value();
    return MilliSeconds(endTime);
}

void Note::moveToTop()
{
    mNoteStartTime_ = NoteStartTime(MilliSeconds(0.0));
}
