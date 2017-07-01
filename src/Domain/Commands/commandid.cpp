#include "commandid.h"

using namespace waltz::engine::Commands;

CommandId::CommandId(const QString& aValue)
    : mValue_(aValue)
{
}

CommandId::CommandId(const CommandId& aOther)
    :mValue_(aOther.mValue_)
{
}

CommandId& CommandId::operator=(const CommandId& aOther)
{
    mValue_ = aOther.mValue_;
    return (*this);
}

bool CommandId::operator==(const CommandId& aOther) const
{
    return mValue_ == aOther.mValue_;
}

bool CommandId::operator!=(const CommandId& aOther) const
{
    return mValue_ != aOther.mValue_;
}

QString CommandId::value() const
{
    return mValue_;
}
