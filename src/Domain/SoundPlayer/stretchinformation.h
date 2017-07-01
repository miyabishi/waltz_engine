#ifndef STRETCHINFORMATION_H
#define STRETCHINFORMATION_H

#include "src/Domain/ScoreComponent/notelength.h"
#include "src/Domain/ScoreComponent/milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace SondPlayer
        {

            class StretchInformation
            {
            public:
                StretchInformation(const waltz::engine::ScoreComponent::NoteLength aNoteLength);
                StretchInformation(const StretchInformation& aOther);
                StretchInformation& operator=(const StretchInformation& aOther);

            private:
                waltz::engine::ScoreComponent::NoteLength mNoteLength_;
            };

        } // namespace SondPlayer
    } // namespace engine
} // namespace waltz

#endif // STRETCHINFORMATION_H
