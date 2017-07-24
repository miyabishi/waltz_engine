#include <QDebug>
#include <QJsonObject>
#include <waltz_common/parameterslist.h>
#include "playscorecommand.h"
#include "src/Domain/ScoreComponent/score.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;

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
    ParametersList noteList(aParameters.find("NoteList").value().toArray());
    qDebug() << noteList.toJsonArray();
    //    waltz::engine::ScoreComponent::Score score;

}
