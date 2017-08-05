#include "pitchchangingpoint.h"
#include "alias.h"
#include "notes.h"
#include <QDebug>

using namespace waltz::engine::ScoreComponent;

Notes::Notes()
{
}

Notes::Notes(const Notes& aOther)
    : mNotes_(aOther.mNotes_)
{
}

Notes& Notes::operator=(const Notes& aOther)
{
    mNotes_ = aOther.mNotes_;
    return (*this);
}

void Notes::append(const NotePointer& aNote)
{
    mNotes_.append(aNote);
}

QVector<waltz::agent::IAlias*> Notes::aliases() const
{
    QVector<waltz::agent::IAlias*> aliasesVector;
    foreach(const NotePointer& note, mNotes_)
    {
        aliasesVector.append((waltz::agent::IAlias*)note->alias());
    }
    return aliasesVector;
}

MilliSeconds Notes::startTime() const
{
    if (mNotes_.length() < 1)
    {
        return MilliSeconds();
    }
    return mNotes_.at(0)->noteStartTime().toMilliSeconds();
}

MilliSeconds Notes::endTime() const
{
    if (mNotes_.length() < 1)
    {
        return MilliSeconds();
    }
    return mNotes_.last()->endTime();
}

MilliSeconds Notes::timeLength() const
{
    return MilliSeconds(endTime().value() - startTime().value());
}
int Notes::length() const
{
    return mNotes_.length();
}

PitchCurvePointer Notes::getPitchCurve() const
{
    PitchCurvePointer pitchCurve(new PitchCurve());
    foreach(const NotePointer& note, mNotes_)
    {
        pitchCurve->append(PitchChangingPointPointer(
                                       new PitchChangingPoint(note->noteStartTime().toMilliSeconds(), note->tone().frequency())));
        pitchCurve->append(PitchChangingPointPointer(
                                       new PitchChangingPoint(MilliSeconds(note->endTime().value() - 0.01) ,
                                                              note->tone().frequency())));
    }
    return pitchCurve;
}
NotePointer Notes::at(int index) const
{
    return mNotes_.at(index);
}

TimeRange Notes::timeRange() const
{
    return TimeRange(startTime(),endTime());
}
