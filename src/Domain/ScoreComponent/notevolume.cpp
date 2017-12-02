#include "notevolume.h"

using namespace waltz::engine::ScoreComponent;

NoteVolume::NoteVolume(int aValue)
    :mValue_(aValue)
{
}

double NoteVolume::calculateSoundValue(double aTargetData) const
{
    return aTargetData * mValue_ / 100.0;
}
