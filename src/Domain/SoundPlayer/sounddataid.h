#ifndef SOUNDDATAID_H
#define SOUNDDATAID_H

#include <QString>

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            class SoundDataId
            {
            public:
                SoundDataId(const QString& aValue);
                SoundDataId(const SoundDataId& aOther);
                SoundDataId operator=(const SoundDataId& aOther);
                bool operator==(const SoundDataId& aOther) const;
                bool operator!=(const SoundDataId& aOther) const;

            private:
                QString mValue_;
            };
        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SOUNDDATAID_H
