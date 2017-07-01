#ifndef PLAYER_H
#define PLAYER_H

#include <QPointer>
#include <QSharedPointer>
#include <QObject>
#include <QAudioOutput>
#include <QBuffer>
#include "sounddatainformation.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            class SoundData;
            class Player : public QObject
            {
                Q_OBJECT

            public:
                Player(QObject* aParent = nullptr);

            public:
                void start(const SoundData& aSoundData);

            private slots:
                void stateChangedHandler(QAudio::State);

            private:
                QPointer<QAudioOutput> mAudioOutput_;
                QBuffer mBuffer_;

            private:
                Player(const Player& aOther);
                Player& operator=(const Player& aOther);
            };
            typedef QSharedPointer<Player> PlayerPointer;

        } // namespace SoundPlayer
    } // namespace Domain
} // namespace waltz

#endif // PLAYER_H
