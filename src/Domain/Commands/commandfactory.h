#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include <waltz_common/command.h>
#include <waltz_common/commandid.h>
#include <QList>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class CommandFactory
            {
            public:
                static CommandFactory& getInstance();
                waltz::common::Commands::CommandPointer createCommand(
                        const waltz::common::Commands::CommandId& aCommandId);
            private:
                CommandFactory();
                static CommandFactory* mInstance_;
                QList<common::Commands::CommandPointer> mCommandList_;
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // COMMANDFACTORY_H
