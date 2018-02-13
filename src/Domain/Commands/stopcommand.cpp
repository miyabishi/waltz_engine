#include<waltz_common/commandid.h>
#include "stopcommand.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;

namespace
{
    const CommandId COMMAND_ID_STOP("Stop");
}

StopCommand::StopCommand()
 :Command(COMMAND_ID_STOP)
{

}
void StopCommand::exec(
        const waltz::common::Commands::Parameters& /*aParameters*/)
{
    waltz::engine::VocalComponent::Vocal::getInstance().stopSinging();
}
