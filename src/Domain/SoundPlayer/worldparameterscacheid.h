#ifndef WORLDPARAMETERSCACHEID_H
#define WORLDPARAMETERSCACHEID_H

#include <QSharedPointer>
#include <QString>

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class WorldParametersCacheId
            {
            public:
                WorldParametersCacheId(const QString& aValue);
                WorldParametersCacheId(const WorldParametersCacheId& aOther);
                WorldParametersCacheId& operator=(const WorldParametersCacheId& aOther);
                bool operator==(const WorldParametersCacheId& aOther) const;
                bool operator!=(const WorldParametersCacheId& aOther) const;
                QString value() const;

            private:
                QString mValue_;

            private:
            };
        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // WORLDPARAMETERSCACHEID_H
