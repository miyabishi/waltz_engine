#include "sounddataid.h"

using namespace waltz::engine::SoundPlayer;

SoundDataId::SoundDataId(const QString& aValue)
    : mValue_(aValue)
{
}

SoundDataId::SoundDataId(const SoundDataId& aOther)
    : mValue_(aOther.mValue_)
{
}

SoundDataId SoundDataId::operator=(const SoundDataId& aOther)
{
    mValue_ = aOther.mValue_;
    return (*this);
}

bool SoundDataId::operator==(const SoundDataId& aOther) const
{
    return mValue_ == aOther.mValue_;
}

bool SoundDataId::operator!=(const SoundDataId& aOther) const
{
    return mValue_ != aOther.mValue_;
}

