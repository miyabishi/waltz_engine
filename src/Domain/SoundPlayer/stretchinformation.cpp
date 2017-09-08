#include "stretchinformation.h"

using namespace waltz::engine::SondPlayer;
using namespace waltz::engine::ScoreComponent;

StretchInformation::StretchInformation(
        const NoteLength aNoteLength)
  :mNoteLength_(aNoteLength)
{
}

StretchInformation::StretchInformation(const StretchInformation &aOther)
  :mNoteLength_(aOther.mNoteLength_)
{
}

StretchInformation& StretchInformation::operator=(const StretchInformation &aOther)
{
    mNoteLength_ = aOther.mNoteLength_;
    return (*this);
}

