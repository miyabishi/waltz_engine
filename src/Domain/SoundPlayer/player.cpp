#include <QDebug>
#include <QDataStream>
#include <QThread>
#include "sounddata.h"
#include "player.h"
#include "src/Notifier/tasktraynotifier.h"

using namespace waltz::engine::SoundPlayer;

Player::Player(QObject* aParent)
    : QObject(aParent)
    , mAudioOutput_(0)
    , mBuffer_()
{
}

void Player::start(const SoundData& aSoundData)
{
    SoundDataInformation soundDataInformation = aSoundData.soundDataInformation();
    QAudioFormat format = soundDataInformation.createAudioFormat();
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    QByteArray byteArray = aSoundData.toByteArray();
    mBuffer_.close();
    mBuffer_.setData(byteArray);
    mBuffer_.open(QIODevice::ReadOnly);

    if (!info.isFormatSupported(format))
    {
        waltz::engine::Notifier::TaskTrayNotifier::getInstance().notifyError("Raw audio format not supported by backend, cannot play audio.");
        return;
    }

    mAudioOutput_ = new QAudioOutput(format, this);
    QThread::sleep(1);
    mAudioOutput_->setNotifyInterval(50);
    //mAudioOutput_->setBufferSize(16 * 1280);
    //mAudioOutput_->setBufferSize(32768);
    mAudioOutput_->setBufferSize(44100);
    connect(mAudioOutput_, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChangedHandler(QAudio::State)));
    mAudioOutput_->start(&mBuffer_);
}

void Player::stateChangedHandler(QAudio::State aNewState)
{
    qDebug() << Q_FUNC_INFO << aNewState;
    switch(aNewState)
    {
    case QAudio::IdleState:
        mAudioOutput_->stop();
        mBuffer_.close();
        delete mAudioOutput_;
        break;
    case QAudio::StoppedState:
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

