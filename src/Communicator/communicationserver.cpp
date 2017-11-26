#include <QtWebSockets/qwebsocketserver.h>
#include <QtWebSockets/qwebsocket.h>
#include "communicationserver.h"
#include "src/Notifier/tasktraynotifier.h"
#include "receiveddata.h"

using namespace waltz::engine::Communicator;
using namespace waltz::common::Communicator;
using namespace waltz::engine::Notifier;


CommunicationServer* CommunicationServer::mInstance_ = 0;

CommunicationServer& CommunicationServer::getInstance()
{
    if(mInstance_ == 0)
    {
        static CommunicationServer instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

CommunicationServer::CommunicationServer()
    : mServer_(new QWebSocketServer(QStringLiteral("Waltz Vocal Engine"),
                                    QWebSocketServer::NonSecureMode,
                                    this))
{    
    if (! mServer_->listen(QHostAddress::LocalHost, 8080))
    {
        return;
    }
    connect(mServer_, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    connect(mServer_, SIGNAL(closed()), this, SIGNAL(closed()));
}

CommunicationServer::~CommunicationServer()
{
    mServer_->close();
    qDeleteAll(mClients_.begin(), mClients_.end());
}

void CommunicationServer::onNewConnection()
{
    QWebSocket *pSocket = mServer_->nextPendingConnection();

    connect(pSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(processMessage(QByteArray)));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    mClients_ << pSocket;
}


void CommunicationServer::processMessage(QByteArray aData)
{
    ReceivedData receivedData(aData);
    receivedData.executeCommand();
}

void CommunicationServer::sendMessage(const Message &aMessage)
{
    foreach (QWebSocket* client, mClients_)
    {
        if(client == 0)
        {
            continue;
        }
        client->sendBinaryMessage(aMessage.toByteArray());
    }
    return;
}

void CommunicationServer::socketDisconnected()
{
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client == 0) return;

    mClients_.removeAll(client);
    client->deleteLater();
}
