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
    const QString PARAMETER_NAME_PLAY_BACK_STARTING_TIME("PlaybackStartingTime");

}

Score::Score(const Parameters& aParameters)
 :  mPhrases_()
 , mPitchCurve_(new PitchCurve())
{
    //TODO: ここでplaybackstartinttimeを考慮すること
    ParametersList noteList(aParameters.find(PARAMETER_NAME_NOTE_LIST).value().toArray());
    ParametersList pitchCurve(aParameters.find(PARAMETER_NAME_PITCH_CURVE).value().toArray());
    MilliSeconds playbackStartingTime
            = MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_PLAY_BACK_STARTING_TIME)
                                        .value().toDouble());

    qDebug() << "playbackstartingtime:" << playbackStartingTime.value();

    if (pitchCurve.size() == 0) return;
    if (noteList.size() == 0) return;

    loadPhrases(noteList, playbackStartingTime);
    loadPitchCurve(pitchCurve, playbackStartingTime);
}

void Score::clear()
{
    mPitchCurve_->clear();
}

void Score::loadPitchCurve(const common::Commands::ParametersList &aPitchCurve,
                           const MilliSeconds& aPlaybackStartingTime)
{
    for(int index = 0; index < aPitchCurve.size(); ++index)
    {
        PitchChangingPointPointer pitchCurve(
                    new PitchChangingPoint(aPitchCurve.at(index), aPlaybackStartingTime));
        mPitchCurve_->append(pitchCurve);
    }
}

void Score::loadPhrases(const common::Commands::ParametersList &aNoteList,
                        const MilliSeconds& aPlaybackStartingTime)
{
    Notes notes;
    int startIndex = 0;

    for(int index = 0; index < aNoteList.size(); ++index)
    {
        NotePointer note(NotePointer(new Note(aNoteList.at(index), MilliSeconds(0))));

        qDebug() << "compare:" << note->noteStartTime().toMilliSeconds().value() << " & "
                 << aPlaybackStartingTime.value();
        if (note->noteStartTime().toMilliSeconds().isSmallerThan(aPlaybackStartingTime))
        {
            continue;
        }

        startIndex=index;
        break;
    }
    qDebug() << "start index" << startIndex;

    notes.append(NotePointer(new Note(aNoteList.at(startIndex), aPlaybackStartingTime)));

    for(int index = startIndex + 1; index < aNoteList.size(); ++index)
    {
        NotePointer note(new Note(aNoteList.at(index), aPlaybackStartingTime));
        if(notes.endTime().value() != note->noteStartTime().toMilliSeconds().value())
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

