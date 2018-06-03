#include "commandfactory.h"
#include "loadvoicelibrarycommand.h"
#include "playnotecommand.h"
#include "playscorecommand.h"
#include "savewavcommand.h"
#include "stopcommand.h"
#include "exitcommand.h"
#include "loaddefaultvoicelibrarycommand.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;


CommandFactory* CommandFactory::mInstance_ = 0;

CommandFactory& CommandFactory::getInstance()
{
    if (0 == mInstance_)
    {
        static CommandFactory instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

CommandPointer CommandFactory::createCommand(const CommandId& aCommandId)
{
    foreach(const CommandPointer command,  mCommandList_)
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
                             new SaveWavCommand()));
    mCommandList_.append(CommandPointer(
                             new StopCommand()));
    mCommandList_.append(CommandPointer(
                             new ExitCommand()));
    mCommandList_.append(CommandPointer(
                             new LoadDefaultVoiceLibraryCommand()));
}
