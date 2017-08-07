
#include <qmath.h>
#include "pitchchangingpoint.h"
#include "alias.h"
#include "notes.h"
#include <QDebug>

using namespace waltz::engine::ScoreComponent;

namespace
{
    double sigmoid(double aX, double aGain)
    {
        return 1/(1 + exp(-aX * aGain));
    }
}

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
    if(mNotes_.length() == 0)
    {
        return PitchCurvePointer();
    }
    qDebug() << Q_FUNC_INFO << "get pitch curve";

    PitchCurvePointer pitchCurve(new PitchCurve());

    NotePointer firstNote = mNotes_.at(0);
    pitchCurve->append(PitchChangingPointPointer(
                                   new PitchChangingPoint(firstNote->noteStartTime().toMilliSeconds(),
                                                          firstNote->tone().frequency())));

    for(int index = 1; index < mNotes_.length(); ++index)
    {

        qDebug() << Q_FUNC_INFO << "note index:" << index;
        double preNoteFrequency = mNotes_.at(index -1 )->tone().frequency();
        NotePointer currentNote = mNotes_.at(index);

        double currentNoteFrequency = currentNote->tone().frequency();
        int portamentoLength = 200;
        double currentTime = currentNote->noteStartTime().toMilliSeconds().value() - portamentoLength;

        for(int pitchCurveIndex = 0; pitchCurveIndex < portamentoLength; ++ pitchCurveIndex)
        {
            double currentFrequency = preNoteFrequency +
                    (currentNoteFrequency - preNoteFrequency) * sigmoid((double)(2 * pitchCurveIndex)/portamentoLength - 1.0, 5.0);

            pitchCurve->append(PitchChangingPointPointer(
                                           new PitchChangingPoint(MilliSeconds(currentTime),
                                                                  currentFrequency)));

            ++currentTime;
        }

        pitchCurve->append(PitchChangingPointPointer(
                                       new PitchChangingPoint(currentNote->noteStartTime().toMilliSeconds(),
                                                              currentNoteFrequency)));
    }
    qDebug() << Q_FUNC_INFO << "get pitch curve finished";
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
