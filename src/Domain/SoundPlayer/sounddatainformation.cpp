#include <QAudioDeviceInfo>
#include "sounddatainformation.h"
#include "src/Notifier/tasktraynotifier.h"
#include "src/Settings/enginesettings.h"

using namespace waltz::engine::SoundPlayer;
using namespace waltz::engine::Settings;


SoundDataInformation::SoundDataInformation()
    : mSampleSize_()
    , mSampleRate_()
{

}

SoundDataInformation::SoundDataInformation(const SampleSize& aSampleSize,
                                           const SampleRate& aSampleRate)
    : mSampleSize_(aSampleSize)
    , mSampleRate_(aSampleRate)
{
}

SoundDataInformation::SoundDataInformation(const SoundDataInformation &aOther)
    : mSampleSize_(aOther.mSampleSize_)
    , mSampleRate_(aOther.mSampleRate_)
{
}

SoundDataInformation& SoundDataInformation::operator=(const SoundDataInformation &aOther)
{
    mSampleSize_ = aOther.mSampleSize_;
    mSampleRate_ = aOther.mSampleRate_;
    return (*this);
}


QAudioFormat SoundDataInformation::createAudioFormat()
{
    QAudioFormat format;
    format.setSampleRate(mSampleRate_.value());
    format.setChannelCount(1);
    format.setSampleSize(mSampleSize_.value());
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(mSampleSize_.sampleType());

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        waltz::engine::Notifier::TaskTrayNotifier::getInstance().notifyError(
                    "Raw audio format not supported by backend, cannot play audio.");
    }

    return format;
}


bool SoundDataInformation::isInitialized() const
{
    return mSampleRate_.isInitialized() && mSampleSize_.isInitialized();
}

int SoundDataInformation::quantizationByte() const
{
    return mSampleSize_.value() / 8;
}

double SoundDataInformation::zeroLine() const
{
    return pow(2.0, mSampleSize_.value() - 1);
}

int SoundDataInformation::calculateIndex(waltz::engine::ScoreComponent::MilliSeconds aMilliSeconds)
{
    return aMilliSeconds.toArrayLength(mSampleRate_);
}

void SoundDataInformation::setWorldParametersToValues(WorldParameters* aWorldParameters)
{
    aWorldParameters->samplingFrequency = mSampleRate_.value();
    aWorldParameters->framePeriod = EngineSettings::getInstance().framePeriod();
}
