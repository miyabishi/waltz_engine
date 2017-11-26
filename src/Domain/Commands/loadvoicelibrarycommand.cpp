#include "loadvoicelibrarycommand.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;
using namespace waltz::engine::VocalComponent;

namespace
{
    const CommandId COMMAND_ID("LoadVoiceLibrary");
    const QString PARAMETER_NAME_FILE_PATH("FilePath");
}

LoadVoiceLibraryCommand::LoadVoiceLibraryCommand()
    : Command(COMMAND_ID)
{
}

void LoadVoiceLibraryCommand::exec(const Parameters& aParameters)
{
    Vocal::getInstance().loadVoiceLibrary(aParameters.find("FilePath").value().toString());
}
