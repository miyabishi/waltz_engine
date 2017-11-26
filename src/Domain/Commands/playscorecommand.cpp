#include <QJsonObject>
#include <waltz_common/parameterslist.h>
#include "playscorecommand.h"
#include "src/Domain/ScoreComponent/score.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::common::Commands;
using namespace waltz::engine::Commands;
using namespace waltz::engine::VocalComponent;

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
    waltz::engine::ScoreComponent::Score score(aParameters);
//    score.clear();
    Vocal::getInstance().sing(score);
}
