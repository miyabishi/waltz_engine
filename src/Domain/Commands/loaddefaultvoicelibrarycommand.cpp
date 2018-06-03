#include <QFileInfo>
#include <QDebug>
#include "loaddefaultvoicelibrarycommand.h"
#include "src/Settings/enginesettings.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;
using namespace waltz::engine::VocalComponent;

namespace
{
    const CommandId COMMAND_ID("LoadDefaultVoiceLibrary");
}

LoadDefaultVoiceLibraryCommand::LoadDefaultVoiceLibraryCommand()
    :Command(COMMAND_ID)
{
}

void LoadDefaultVoiceLibraryCommand::exec(const Parameters& /*aParameters*/)
{
    QFileInfo info;
    QString path = Settings::EngineSettings::getInstance().defaultVoiceLibraryPath();
    qDebug() << "momo path" << path;
    if (! info.exists(path)) return;

    Vocal::getInstance().loadVoiceLibrary(path);
}
