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
    , mByteArray_()
    , mDataStream_()
{
}

Player::~Player()
{
}

void Player::start(const SoundData& aSoundData)
{
    aSoundData.outputWaveDataForDebug("play_data.txt");
    SoundDataInformation soundDataInformation = aSoundData.soundDataInformation();
    QAudioFormat format = soundDataInformation.createAudioFormat();
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

    if (!info.isFormatSupported(format))
    {
        waltz::engine::Notifier::TaskTrayNotifier::getInstance().notifyError("Raw audio format not supported by backend, cannot play audio.");
        return;
    }

    mAudioOutput_ = QSharedPointer<QAudioOutput>(new QAudioOutput(format, this));
    mByteArray_ = QSharedPointer<QByteArray>(new QByteArray(aSoundData.toByteArray()));
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
    //        mAudioOutput_->stop();
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

