#include <QJsonObject>
#include <QJsonDocument>

#include "message.h"

using namespace waltz::engine::Communicator;
using namespace waltz::engine::Commands;

namespace
{
    const QString COMMAND_ID_KEY = "CommandId";
    const QString PARAMETERS_KEY  = "Parameters";
}

Message::Message(const CommandId& aCommandId,
                 const Parameters& aParameters)
    : mCommandId_(aCommandId)
    , mParameters_(aParameters)
{
}

Message::Message(const Message& aOther)
    : mCommandId_(aOther.mCommandId_)
    , mParameters_(aOther.mParameters_)
{
}

Message& Message::operator=(const Message& aOther)
{
    mCommandId_ = aOther.mCommandId_;
    mParameters_ = aOther.mParameters_;

    return (*this);
}

QByteArray Message::toByteArray() const
{
    QJsonObject jsonObject;
    jsonObject[COMMAND_ID_KEY] = mCommandId_.value();
    jsonObject[PARAMETERS_KEY] = mParameters_.toJsonArray();
    QJsonDocument jsonDocument(jsonObject);

    return jsonDocument.toJson(QJsonDocument::Compact);
}

