#include <QDebug>
#include <waltz_common/parameterslist.h>
#include "phrase.h"
#include "score.h"
#include "notes.h"

using namespace waltz::common::Commands;
using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;

namespace
{
    const QString PARAMETER_NAME_NOTE_LIST("NoteList");
}

Score::Score(const Parameters& aParameters)
{
    qDebug() << "score constructor";
    qDebug() << aParameters.find(PARAMETER_NAME_NOTE_LIST).value().toArray();
    ParametersList noteList(aParameters.find(PARAMETER_NAME_NOTE_LIST).value().toArray());
    if (noteList.size() == 0)
    {
        return;
    }

    Notes notes;
    notes.append(NotePointer(new Note(noteList.at(0))));

    for(int index = 1; index < noteList.size(); ++index)
    {
        NotePointer note(new Note(noteList.at(index)));
        if(notes.endTime().value() != note->noteStartTime().toMilliSeconds().value())
        {
            qDebug() << Q_FUNC_INFO << "create new Phrase";
            mPhrases_.apend(PhrasePointer(new Phrase(notes)));
            notes = Notes();
        }
        notes.append(note);
    }
    mPhrases_.apend(PhrasePointer(new Phrase(notes)));
}


Score::Score(const Phrases& aPhrases)
    :mPhrases_(aPhrases)
{
}
Score::Score(const Score& aOther)
    :mPhrases_(aOther.mPhrases_)
{
}

Score& Score::operator=(const Score& aOther)
{
    mPhrases_ = aOther.mPhrases_;
    return (*this);
}

SoundData Score::toSoundData() const
{
    qDebug() << Q_FUNC_INFO;
    return mPhrases_.toSoundData();
}

