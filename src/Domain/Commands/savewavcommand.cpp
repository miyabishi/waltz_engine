#include <waltz_common/commandid.h>

#include "src/Domain/ScoreComponent/score.h"
#include "src/FileIO/wavfile.h"
#include "savewavcommand.h"

using namespace waltz::common::Commands;
using namespace waltz::engine::Commands;
using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::FileIO;

namespace
{
    const CommandId COMMAND_ID("SaveWav");
}

SaveWavCommand::SaveWavCommand()
    : Command(COMMAND_ID)
{
}

void SaveWavCommand::exec(const waltz::common::Commands::Parameters& aParameters)
{
    Score score(aParameters);
    WavFile wav(aParameters.find("FilePath").value().toString());
    wav.write(score.toSoundData());
}
