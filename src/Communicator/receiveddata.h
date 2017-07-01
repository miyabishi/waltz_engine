#ifndef RECEIVEDDATA_H
#define RECEIVEDDATA_H

#include <QByteArray>
#include "src/Domain/Commands/commandid.h"
#include "src/Domain/Commands/parameters.h"


namespace waltz
{
    namespace engine
    {
        namespace Communicator
        {
            class ReceivedData
            {
            public:
                explicit ReceivedData(
                        const QByteArray& aReceivedData);
                ReceivedData(const ReceivedData& aOther);
                ReceivedData& operator=(const ReceivedData& aOther);
                ~ReceivedData();
                void executeCommand();

            private:
                void parseReceivedData(const QByteArray& aReceivedData);
                waltz::engine::Commands::Parameters parseParameters(const QJsonArray& aParameterArray) const;

            private:
                waltz::engine::Commands::CommandId  mCommandId_;
                waltz::engine::Commands::Parameters mParameters_;
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // RECEIVEDDATA_H
