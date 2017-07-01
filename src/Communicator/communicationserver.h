#ifndef COMMUNICATIONSERVER_H
#define COMMUNICATIONSERVER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QByteArray>
#include "message.h"

class QWebSocketServer;
class QWebSocket;

namespace waltz
{
    namespace engine
    {
        namespace Communicator
        {
            class CommunicationServer : public QObject
            {
                Q_OBJECT
            public:
                static CommunicationServer& getInstance();

            public:
                void sendMessage(const Message& aMessage);

            signals:
                void closed();

            private slots:
                void onNewConnection();
                void processMessage(QByteArray aData);
                void socketDisconnected();

            private:
                static CommunicationServer* mInstance_;
                QWebSocketServer*           mServer_;
                QList<QWebSocket*>          mClients_;

            private:
                explicit CommunicationServer();
                ~CommunicationServer();
            };

        } // namespace Communicator
    } // namespace engine
} // namespace waltz

#endif // COMMUNICATIONSERVER_H
