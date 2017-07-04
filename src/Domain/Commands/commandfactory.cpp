#include "commandfactory.h"
#include "loadvoicelibrarycommand.h"
#include "playnotecommand.h"
#include "playscorecommand.h"

using namespace waltz::engine::Commands;

CommandPointer CommandFactory::createCommand(const CommandId& aCommandId)
{
    if(aCommandId == CommandId("LoadVoiceLibrary"))
    {
        return CommandPointer(
                    new LoadVoiceLibraryCommand());
    }
    if(aCommandId == CommandId("PlayNote"))
    {
        return CommandPointer(
                    new PlayNoteCommand());
    }
    if(aCommandId == CommandId("PlayScore"))
    {
        return CommandPointer(
                    new PlayScoreCommand());
    }

    return CommandPointer();
}

CommandFactory::CommandFactory()
{
}
