#ifndef MESSAGE_H
#define MESSAGE_H

#include "src/Domain/Commands/commandid.h"
#include "src/Domain/Commands/parameters.h"

namespace waltz
{
    namespace engine
    {
        namespace Communicator
        {
            class Message
            {
            public:
                Message(const waltz::engine::Commands::CommandId& aCommandId,
                        const waltz::engine::Commands::Parameters& aParameters);
                Message(const Message& aOther);
                Message& operator=(const Message& aOther);

            public:
                QByteArray toByteArray() const;

            private:
                waltz::engine::Commands::CommandId  mCommandId_;
                waltz::engine::Commands::Parameters mParameters_;
            };

        } // namespace Communicator
    } // namespace engine
} // namespace waltz

#endif // MESSAGE_H
