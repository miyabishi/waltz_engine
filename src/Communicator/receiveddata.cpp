#include <QtDebug>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <waltz_common/command.h>
#include <waltz_common/parameters.h>
#include <waltz_common/parameter.h>

#include "receiveddata.h"
#include "src/Notifier/tasktraynotifier.h"
#include "src/Domain/Commands/commandfactory.h"

using namespace waltz::engine::Communicator;
using namespace waltz::engine::Commands;
using namespace waltz::common::Commands;
using namespace waltz::engine::Notifier;

namespace
{
    const QString COMMAND_ID_KEY = "CommandId";
    const QString PARAMETERS_KEY  = "Parameters";
}

ReceivedData::ReceivedData(const QByteArray& aRecieivedData)
    : mCommandId_("")
    , mParameters_()
{
    parseReceivedData(aRecieivedData);
}

ReceivedData::~ReceivedData()
{
}

ReceivedData::ReceivedData(const ReceivedData& aOther)
    : mCommandId_(aOther.mCommandId_)
    , mParameters_(aOther.mParameters_)
{
}

ReceivedData& ReceivedData::operator=(const ReceivedData& aOther)
{
    mCommandId_  = aOther.mCommandId_;
    mParameters_ = aOther.mParameters_;
    return (*this);
}

void ReceivedData::parseReceivedData(const QByteArray &aReceivedData)
{
    QJsonParseError error;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(aReceivedData, &error));
    qDebug() << jsonDocument;
    if (error.error != QJsonParseError::NoError)
    {
        TaskTrayNotifier::getInstance().notifyError(error.errorString());
        qWarning() << error.errorString();
        return;
    }
    QJsonObject jsonObject(jsonDocument.object());

    mCommandId_ = CommandId(jsonObject.value(COMMAND_ID_KEY).toString());
    mParameters_ = Parameters(jsonObject.value(PARAMETERS_KEY).toArray());
}

void ReceivedData::executeCommand()
{
    CommandPointer command = CommandFactory::getInstance().createCommand(mCommandId_);
    if (command == 0)
    {
        return;
    }
    command->exec(mParameters_);
}


