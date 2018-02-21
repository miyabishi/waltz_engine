#include <QJsonObject>
#include <waltz_common/parameterslist.h>
#include "src/Domain/ScoreComponent/milliseconds.h"
#include "playscorecommand.h"
#include "src/Domain/ScoreComponent/score.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::common::Commands;
using namespace waltz::engine::Commands;
using namespace waltz::engine::VocalComponent;
using namespace waltz::engine::ScoreComponent;

namespace
{
    const CommandId COMMAND_ID_PLAY_SCORE("PlayScore");
    const QString PARAMETER_PLAY_BACK_STARTING_TIME("PlayBackStartingTime");
}

PlayScoreCommand::PlayScoreCommand()
    : Command(COMMAND_ID_PLAY_SCORE)
{
}

void PlayScoreCommand::exec(const Parameters &aParameters)
{
    MilliSeconds playBackStartingTime =
            MilliSeconds::fromSeconds(aParameters.find(PARAMETER_PLAY_BACK_STARTING_TIME).value().toDouble());

    waltz::engine::ScoreComponent::Score score(aParameters);
    Vocal::getInstance().sing(score, playBackStartingTime);
}
