#include "worldparameterscacheid.h"

using namespace waltz::engine::SoundPlayer;

WorldParametersCacheId::WorldParametersCacheId(const QString& aValue)
    :mValue_(aValue)
{
}

WorldParametersCacheId::WorldParametersCacheId(const WorldParametersCacheId& aOther)
    :mValue_(aOther.mValue_)
{

}

WorldParametersCacheId& WorldParametersCacheId::operator=(const WorldParametersCacheId& aOther)
{
    mValue_ = aOther.mValue_;
    return (*this);
}

bool WorldParametersCacheId::operator==(const WorldParametersCacheId& aOther) const
{
    return mValue_ == aOther.mValue_;
}

bool WorldParametersCacheId::operator!=(const WorldParametersCacheId& aOther) const
{
    return mValue_ != aOther.mValue_;
}

QString WorldParametersCacheId::value() const
{
    return mValue_;
}
