#include "commandfactory.h"
#include "loadvoicelibrarycommand.h"
#include "playnotecommand.h"
#include "playscorecommand.h"
#include "savewavcommand.h"
#include "stopcommand.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;


CommandPointer CommandFactory::createCommand(const CommandId& aCommandId)
{
    foreach(CommandPointer command,  mCommandList_)
    {
        if(! command->commandIdEquals(aCommandId)) continue;
        return command;
    }


    return CommandPointer();
}

CommandFactory::CommandFactory()
{
    mCommandList_.append(CommandPointer(
                             new LoadVoiceLibraryCommand()));
    mCommandList_.append(CommandPointer(
                             new PlayNoteCommand()));
    mCommandList_.append(CommandPointer(
                             new PlayScoreCommand()));
    mCommandList_.append(CommandPointer(
                             new SaveWavCommand());
    mCommandList_.append(CommandPointer(
                             new StopCommand());
}
