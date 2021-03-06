#include <QDebug>

#include "phrase.h"
#include "score.h"
#include "notes.h"

using namespace waltz::common::Commands;
using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;

namespace
{
    const QString PARAMETER_NAME_NOTE_LIST("NoteList");
    const QString PARAMETER_NAME_PITCH_CURVE("PitchCurve");

}

Score::Score(const Parameters& aParameters)
 :  mPhrases_()
 , mPitchCurve_(new PitchCurve())
{
    ParametersList noteList(aParameters.find(PARAMETER_NAME_NOTE_LIST).value().toArray());
    ParametersList pitchCurve(aParameters.find(PARAMETER_NAME_PITCH_CURVE).value().toArray());

    if (pitchCurve.size() == 0) return;
    if (noteList.size() == 0) return;

    loadPhrases(noteList);
    loadPitchCurve(pitchCurve);
}

void Score::clear()
{
    mPitchCurve_->clear();
}

void Score::loadPitchCurve(const common::Commands::ParametersList &aPitchCurve)
{
    for(int index = 0; index < aPitchCurve.size(); ++index)
    {
        PitchChangingPointPointer pitchCurve(
                    new PitchChangingPoint(aPitchCurve.at(index)));
        mPitchCurve_->append(pitchCurve);
    }
}

void Score::loadPhrases(const common::Commands::ParametersList &aNoteList)
{
    Notes notes;
    notes.append(NotePointer(new Note(aNoteList.at(0))));

    for(int index = 1; index < aNoteList.size(); ++index)
    {
        NotePointer note(new Note(aNoteList.at(index)));
        if(qAbs(notes.endTime().value() - note->noteStartTime().toMilliSeconds().value()) > 2 )
        {
            mPhrases_.apend(PhrasePointer(new Phrase(notes)));
            notes = Notes();
        }
        notes.append(note);
    }
    mPhrases_.apend(PhrasePointer(new Phrase(notes)));
}

Score::Score(const Score& aOther)
    : mPhrases_(aOther.mPhrases_)
    , mPitchCurve_(aOther.mPitchCurve_)
{
}

Score& Score::operator=(const Score& aOther)
{
    mPhrases_ = aOther.mPhrases_;
    mPitchCurve_ = aOther.mPitchCurve_;
    return (*this);
}

SoundDataPointer Score::toSoundData() const
{
    return mPhrases_.toSoundData(mPitchCurve_);
}

