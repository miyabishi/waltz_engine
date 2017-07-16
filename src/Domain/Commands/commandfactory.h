#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <waltz_common/command.h>
#include <waltz_common/commandid.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class CommandFactory
            {
            public:
                static waltz::common::Commands::CommandPointer createCommand(
                        const waltz::common::Commands::CommandId& aCommandId);
            private:
                CommandFactory();
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // COMMANDFACTORY_H
