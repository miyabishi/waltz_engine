#include "playscorecommand.h"

using namespace waltz::engine::Commands;

namespace
{
    const CommandId COMMAND_ID_PLAY_SCORE("PlayScore");
}

PlayScoreCommand::PlayScoreCommand()
    : Command(COMMAND_ID_PLAY_SCORE)
{
}

void PlayScoreCommand::exec(const Parameters &aParameters)
{
}
