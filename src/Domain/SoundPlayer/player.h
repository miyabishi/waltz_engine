#ifndef PLAYER_H
#define PLAYER_H

#include <QSharedPointer>
#include <QObject>
#include <QAudioOutput>
#include <QBuffer>
#include "sounddatainformation.h"
#include "sounddata.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            class Player : public QObject
            {
                Q_OBJECT

            public:
                Player(QObject* aParent = nullptr);
                ~Player();

            public:
                void start(SoundDataPointer aSoundData);

            private slots:
                void stateChangedHandler(QAudio::State);

            private:
                QSharedPointer<QAudioOutput> mAudioOutput_;
                QSharedPointer<QByteArray> mByteArray_;
                QSharedPointer<QDataStream> mDataStream_;

            private:
                Player(const Player& aOther);
                Player& operator=(const Player& aOther);
            };
            typedef QSharedPointer<Player> PlayerPointer;

        } // namespace SoundPlayer
    } // namespace Domain
} // namespace waltz

#endif // PLAYER_H
