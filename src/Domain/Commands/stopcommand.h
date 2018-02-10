#ifndef STOPCOMMAND_H
#define STOPCOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {

            class StopCommand : common::Commands::Command
            {
            public:
                StopCommand();
            public:
                void exec(
                        const waltz::common::Commands::Parameters &aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // STOPCOMMAND_H
