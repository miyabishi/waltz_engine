#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "command.h"
#include "commandid.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class CommandFactory
            {
            public:
                static CommandPointer createCommand(const CommandId& aCommandId);
            private:
                CommandFactory();
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // COMMANDFACTORY_H
