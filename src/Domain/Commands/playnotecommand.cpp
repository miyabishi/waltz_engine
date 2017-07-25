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
}

PlayNoteCommand::PlayNoteCommand()
    : Command(COMMAND_ID_PLAY_NOTE)
{
}

void PlayNoteCommand::exec(const Parameters& /*aParameters*/)
{
    /*
    Note note(aParameters);
    Vocal::getInstance().singSingleNote(note);
    */
}
