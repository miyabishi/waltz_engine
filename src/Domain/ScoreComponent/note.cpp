#include "note.h"

using namespace waltz::engine::ScoreComponent;

namespace
{
    const QString PARAMETER_NAME_TONE_VALUE("ToneValue");
    const QString PARAMETER_NAME_TONE_OCTAVE("Octave");
    const QString PARAMETER_NAME_ALIAS("Alias");
    const QString PARAMETER_NAME_NOTE_START_TIME("NoteStartTime");
    const QString PARAMETER_NAME_NOTE_LENGTH("NoteLength");
    const QString PARAMETER_NAME_NOTE_VOLUME("NoteVolume");
}

Note::Note(const waltz::common::Commands::Parameters& aParameters)
    : mTone_((ToneValue)aParameters.find(PARAMETER_NAME_TONE_VALUE).value().toInt(),
               aParameters.find(PARAMETER_NAME_TONE_OCTAVE).value().toInt())
    , mAlias_(* (new Alias(aParameters.find(PARAMETER_NAME_ALIAS).value().toString())))
    , mNoteStartTime_(MilliSeconds(aParameters.find(PARAMETER_NAME_NOTE_START_TIME).value().toDouble()*1000.0))
    , mNoteLength_(MilliSeconds(aParameters.find(PARAMETER_NAME_NOTE_LENGTH).value().toDouble()*1000.0))
    , mNoteVolume_(NoteVolumePointer(new NoteVolume(aParameters.find(PARAMETER_NAME_NOTE_VOLUME).value().toInt())))
{
}

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
    , mNoteVolume_(aOther.mNoteVolume_)
{

}

Note& Note::operator=(const Note& aOther)
{
    mTone_ = aOther.mTone_;
    mAlias_ = aOther.mAlias_;
    mNoteStartTime_ = aOther.mNoteStartTime_;
    mNoteLength_ = aOther.mNoteLength_;
    mNoteVolume_ = aOther.mNoteVolume_;

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

NoteVolumePointer Note::noteVolume() const
{
    return mNoteVolume_;
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

Tone Note::tone() const
{
    return mTone_;
}

TimeRange Note::noteTimeRange() const
{
    return TimeRange(noteStartTime().toMilliSeconds(),
                     noteStartTime().toMilliSeconds().add(mNoteLength_.toMilliSeconds()));
}
