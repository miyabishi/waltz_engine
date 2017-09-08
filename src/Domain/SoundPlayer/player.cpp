#include <QDebug>
#include <QDataStream>
#include <QThread>
#include <waltz_common/parameters.h>
#include <waltz_common/message.h>
#include <waltz_common/commandid.h>
#include "sounddata.h"
#include "player.h"
#include "src/Notifier/tasktraynotifier.h"
#include "src/Communicator/communicationserver.h"
#include "src/FileIO/wavfile.h"


using namespace waltz::common::Communicator;
using namespace waltz::common::Commands;
using namespace waltz::engine::Communicator;
using namespace waltz::engine::SoundPlayer;


namespace
{
    const CommandId COMMAND_ID_ACTIVE_PLAY_BUTTON("ActivePlayButton");
}

Player::Player(QObject* aParent)
    : QObject(aParent)
    , mAudioOutput_(0)
    , mByteArray_()
    , mDataStream_()
{
}

Player::~Player()
{
}

void Player::start(SoundDataPointer aSoundData)
{
    FileIO::WavFile wav("test.wav");
    wav.write(aSoundData);
    qDebug() << Q_FUNC_INFO;
    aSoundData->outputWaveDataForDebug("play_data.txt");
    SoundDataInformationPointer soundDataInformation = aSoundData->soundDataInformation();
    QAudioFormat format = soundDataInformation->createAudioFormat();
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

    if (!info.isFormatSupported(format))
    {
        waltz::engine::Notifier::TaskTrayNotifier::getInstance().notifyError("Raw audio format not supported by backend, cannot play audio.");
        return;
    }

    mAudioOutput_ = QSharedPointer<QAudioOutput>(new QAudioOutput(format, this));
    mByteArray_ = QSharedPointer<QByteArray>(new QByteArray(aSoundData->toByteArray()));
    mDataStream_ = QSharedPointer<QDataStream>(new QDataStream(mByteArray_.data(), QIODevice::ReadWrite));
    QThread::sleep(1);
    mAudioOutput_->setNotifyInterval(50);
    mAudioOutput_->setBufferSize(16 * 1280);
    connect(mAudioOutput_.data(), SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChangedHandler(QAudio::State)));
    mAudioOutput_->start(mDataStream_->device());
    return;
}

void Player::stateChangedHandler(QAudio::State aNewState)
{
    qDebug() << Q_FUNC_INFO << aNewState;
    switch(aNewState)
    {
    case QAudio::IdleState:
        CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_ACTIVE_PLAY_BUTTON));
        break;
    case QAudio::StoppedState:
        CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_ACTIVE_PLAY_BUTTON));
        if (mAudioOutput_->error() == QAudio::NoError) {
            return;
        }
        mAudioOutput_->stop();
        waltz::engine::Notifier::TaskTrayNotifier::getInstance().notifyError("audio output error.");
        break;
    default:

        break;
    }
}

