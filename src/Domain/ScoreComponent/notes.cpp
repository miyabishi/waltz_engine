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

void Notes::append(const Note& aNote)
{
    mNotes_.append(aNote);
}

QVector<waltz::agent::IAlias*> Notes::aliases() const
{
    QVector<waltz::agent::IAlias*> aliasesVector;
    foreach(const Note& note, mNotes_)
    {
        aliasesVector.append((waltz::agent::IAlias*)note.alias());
    }
    return aliasesVector;
}

MilliSeconds Notes::startTime() const
{
    if (mNotes_.length() < 1)
    {
        return MilliSeconds();
    }
    return mNotes_.at(0).noteStartTime().toMilliSeconds();
}

MilliSeconds Notes::endTime() const
{
    if (mNotes_.length() < 1)
    {
        return MilliSeconds();
    }
    return mNotes_.last().endTime();
}

MilliSeconds Notes::length() const
{
    return MilliSeconds(endTime().value() - startTime().value());
}

PitchCurvePointer Notes::getPitchCurve() const
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << "f0 array length (expect):" << length().toF0ArrayLength();
    return PitchCurvePointer(new PitchCurve());
}
