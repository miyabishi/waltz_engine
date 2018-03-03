#include <QJsonObject>
#include <waltz_common/parameterslist.h>
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
    const QString PARAMETER_NAME_PLAY_BACK_STARTING_TIME("PlaybackStartingTime");
}

PlayScoreCommand::PlayScoreCommand()
    : Command(COMMAND_ID_PLAY_SCORE)
{
}

void PlayScoreCommand::exec(const Parameters &aParameters)
{
    waltz::engine::ScoreComponent::Score score(aParameters);
    MilliSeconds aPlybackStartingTime = MilliSeconds::fromSeconds(
                aParameters.find(PARAMETER_NAME_PLAY_BACK_STARTING_TIME).value().toDouble());
    Vocal::getInstance().sing(score, aPlybackStartingTime);
}
