#ifndef NOTE_H
#define NOTE_H

#include <QSharedPointer>
#include <waltz_common/parameters.h>
#include "tone.h"
#include "alias.h"
#include "notestarttime.h"
#include "notelength.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {

            class Note
            {
            public:
                Note(const waltz::common::Commands::Parameters& aParameters);
                Note(const Tone& aTone,
                     const Alias& aAlias,
                     const NoteStartTime& aNoteStartTime,
                     const NoteLength& aNoteLength);
                Note(const Note& aOther);
                Note& operator=(const Note& aOther);
                ~Note();

            public:
                Alias* alias() const;
                NoteLength noteLength() const;
                NoteStartTime noteStartTime() const;
                MilliSeconds endTime() const;
                void moveToTop();

            private:
                Tone          mTone_;
                Alias&        mAlias_;
                NoteStartTime mNoteStartTime_;
                NoteLength    mNoteLength_;
            };
            typedef QSharedPointer<Note> NotePointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // NOTE_H
