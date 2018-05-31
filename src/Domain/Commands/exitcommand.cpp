#include "exitcommand.h"
#include <QApplication>
#include <waltz_common/commandid.h>

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;

namespace
{
    const CommandId COMMAND_ID("Exit");
}


ExitCommand::ExitCommand()
    :Command(COMMAND_ID)
{

}

void ExitCommand::exec(const waltz::common::Commands::Parameters& /*aParameters*/)
{
    QApplication::exit(0);
}

