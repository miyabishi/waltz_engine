#ifndef COMMAND_H
#define COMMAND_H

#include <QSharedPointer>
#include "commandid.h"
#include "parameters.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class Command
            {
            public:
                explicit Command(const CommandId& aCommandId);
                virtual ~Command();
                bool operator==(Command& aOther);

            public:
                virtual void exec(const Parameters& aParameters) = 0;

            private:
                CommandId  mCommandId_;

            private:
                Command(const Command& aOther);
                Command& operator=(const Command& aOther);
            };
            typedef QSharedPointer<Command>(CommandPointer);
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // COMMAND_H
