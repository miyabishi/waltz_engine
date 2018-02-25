#ifndef NOTES_H
#define NOTES_H

#include <QList>
#include <QVector>
#include <ialias.h>
#include "timerange.h"
#include "pitchcurve.h"
#include "note.h"
#include "milliseconds.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Notes
            {
            public:
                Notes();
                Notes(const Notes& aOther);
                Notes& operator=(const Notes& aOther);

            public:
                void append(const NotePointer& aNote);
                QVector<waltz::agent::IAlias*> aliases() const;
                MilliSeconds startTime() const;
                MilliSeconds endTime() const;
                MilliSeconds timeLength() const;
                int length() const;
                NotePointer at(int index) const;
                TimeRange timeRange() const;
            private:
                QList<NotePointer> mNotes_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // NOTES_H
