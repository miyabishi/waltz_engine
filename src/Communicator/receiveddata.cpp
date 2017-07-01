#include <QtDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "receiveddata.h"
#include "src/Notifier/tasktraynotifier.h"
#include "src/Domain/Commands/command.h"
#include "src/Domain/Commands/commandfactory.h"
#include "src/Domain/Commands/parameters.h"
#include "src/Domain/Commands/parameter.h"

using namespace waltz::engine::Communicator;
using namespace waltz::engine::Commands;
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
    if (error.error != QJsonParseError::NoError)
    {
        TaskTrayNotifier::getInstance().notifyError(error.errorString());
        qWarning() << error.errorString();
        return;
    }
    QJsonObject jsonObject(jsonDocument.object());

    mCommandId_ = CommandId(jsonObject.value(COMMAND_ID_KEY).toString());
    mParameters_ = Parameters(parseParameters(jsonObject.value(PARAMETERS_KEY).toArray()));
}

void ReceivedData::executeCommand()
{
    CommandPointer command = CommandFactory::createCommand(mCommandId_);
    if (command == 0)
    {
        return;
    }
    command->exec(mParameters_);
}


Parameters ReceivedData::parseParameters(const QJsonArray& aParameterArray) const
{
    Parameters parameters;
    foreach(const QJsonValue& value, aParameterArray)
    {
        QJsonObject object = value.toObject();
        parameters.append(Parameter(object.take(PARAMETER_KEY_NAME).toString(),
                                    object.take(PARAMETER_KEY_VALUE).toVariant()));
    }
    return parameters;
}
