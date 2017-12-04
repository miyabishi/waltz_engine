#include <QDataStream>
#include <QThread>
#include <waltz_common/parameters.h>
#include <waltz_common/message.h>
#include <waltz_common/commandid.h>
#include "sounddata.h"
#include "player.h"
#include "src/Notifier/tasktraynotifier.h"
#include "src/Communicator/communicationserver.h"

using namespace waltz::common::Communicator;
using namespace waltz::common::Commands;
using namespace waltz::engine::Communicator;
using namespace waltz::engine::SoundPlayer;


namespace
{
    const CommandId COMMAND_ID_ACTIVE_PLAY_BUTTON("ActivePlayButton");
    const CommandId COMMAND_ID_START_SEEK_BAR("StartSeekBar");
    const CommandId COMMAND_ID_RESET_SEEK_BAR("ResetSeekBar");
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
    CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_START_SEEK_BAR));
    return;
}

void Player::stateChangedHandler(QAudio::State aNewState)
{
    switch(aNewState)
    {
    case QAudio::IdleState:
        CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_ACTIVE_PLAY_BUTTON));
        CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_RESET_SEEK_BAR));
        break;
    case QAudio::StoppedState:
            CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_ACTIVE_PLAY_BUTTON));
        CommunicationServer::getInstance().sendMessage(Message(COMMAND_ID_RESET_SEEK_BAR));
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

