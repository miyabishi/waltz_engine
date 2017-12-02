#ifndef NOTEVOLUME_H
#define NOTEVOLUME_H

#include <QSharedPointer>

namespace waltz
{

    namespace engine
    {
        namespace ScoreComponent
        {

            class NoteVolume
            {
            public:
                explicit NoteVolume(int aValue);
                double calculateSoundValue(double aTargetData) const;

            private:
                int mValue_;

            private:
                NoteVolume(const NoteVolume& aOther);
                NoteVolume& operator=(const NoteVolume& aOther);
            };
            typedef QSharedPointer<NoteVolume> NoteVolumePointer;

        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // NOTEVOLUME_H
