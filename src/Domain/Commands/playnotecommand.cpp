#include <QDebug>
#include <waltz_common/commandid.h>
#include <waltz_common/parameters.h>

#include "src/Domain/VocalComponent/vocal.h"
#include "src/Domain/ScoreComponent/note.h"
#include "playnotecommand.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;
using namespace waltz::engine::VocalComponent;
using namespace waltz::engine::ScoreComponent;

namespace
{
    const CommandId COMMAND_ID_PLAY_NOTE ("PlayNote");
    const QString PARAMETER_NAME_TONE_VALUE("ToneValue");
    const QString PARAMETER_NAME_TONE_OCTAVE("Octave");
    const QString PARAMETER_NAME_TONE_ALIAS("Alias");
    const QString PARAMETER_NAME_TONE_NOTE_START_TIME("NoteStartTime");
    const QString PARAMETER_NAME_TONE_NOTE_LENGTH("NoteLength");
}

PlayNoteCommand::PlayNoteCommand()
    : Command(COMMAND_ID_PLAY_NOTE)
{
}

void PlayNoteCommand::exec(const Parameters& aParameters)
{
    Note note(aParameters);
    Vocal::getInstance().singSingleNote(note);
}
