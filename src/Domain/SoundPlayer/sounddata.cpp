#include <QDebug>
#include <memory>
#include <QDataStream>
#include <QBuffer>
#include "sounddata.h"

using namespace waltz::engine::SoundPlayer;
using namespace waltz::engine::ScoreComponent;

using namespace waltz::engine::SoundPlayer;

namespace
{
    double linearFunction(const int aIndex,
                          const int aLength,
                          const double aStartValue,
                          const double aEndValue)
    {
        double slope = (aEndValue - aStartValue)/(double)aLength;
        return slope * aIndex + aStartValue;
    }

    double fadeInFunction(const int aIndex,
                          const int aLength)
    {
        return linearFunction(aIndex,
                              aLength,
                              0,
                              1);
    }

    double fadeOutFunction(const int aIndex,
                                const int aLength)
    {
        return linearFunction(aIndex,
                              aLength,
                              1,
                              0);
    }
}

SoundData::SoundData()
    : mSoundVector_()
    , mSoundDataInformation_()
{
}

SoundData::SoundData(const QByteArray& aData,
                     const SoundDataInformation& aSoundDataInformation)
    : mSoundVector_()
    , mSoundDataInformation_(aSoundDataInformation)
{
    initializeWavDataByByteArray(aData);
}

SoundData::~SoundData()
{
}

void SoundData::initializeWavDataByByteArray(const QByteArray& aByteArray)
{
    mSoundVector_.clear();
    QBuffer buffer;
    buffer.setData(aByteArray);
    buffer.open(QIODevice::ReadOnly);

    int quantization_byte = mSoundDataInformation_.quantizationByte();
    double zero_line = mSoundDataInformation_.zeroLine();

    QDataStream stream(aByteArray);
    stream.setByteOrder(QDataStream::LittleEndian);
    int lengthOfOutput = aByteArray.length() / quantization_byte;

    for (int index = 0; index < lengthOfOutput; ++index)
    {
        qint16 out;
        stream >> out;
        mSoundVector_.append(out / zero_line);
    }
}


QByteArray SoundData::toByteArray() const
{
    QByteArray byteArray;

    QBuffer buffer;
    buffer.setBuffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream.setByteOrder(QDataStream::LittleEndian);
    for (int index = 0; index < mSoundVector_.size(); ++index)
    {
        int16_t tmp_signal = roudedSoundValue(index);
        stream << tmp_signal;
    }

    return byteArray;
}

int16_t SoundData::roudedSoundValue(int aIndex) const
{
    int value = (int)(mSoundVector_.at(aIndex) * 32767);
    if (value > 32767)
    {
        return 32767;
    }
    if (value < -32768)
    {
        return -32768;
    }
    return value;
}

SoundData::SoundData(const SoundData& aOther)
    : mSoundVector_(aOther.mSoundVector_)
    , mSoundDataInformation_(aOther.mSoundDataInformation_)
{
}

SoundData& SoundData::operator=(const SoundData& aOther)
{
    mSoundVector_ = aOther.mSoundVector_;
    mSoundDataInformation_ = aOther.mSoundDataInformation_;

    return (*this);
}

QVector<double> SoundData::toVector() const
{
    return mSoundVector_;
}

void SoundData::appendData(const SoundData &aSoundData, const MilliSeconds &aStartTime)
{
    updateInformationIfNotInitialized(aSoundData.soundDataInformation());
    int startTimeIndex = mSoundDataInformation_.calculateIndex(aStartTime);
    qDebug() << Q_FUNC_INFO
             << "starttime index" << startTimeIndex
             << "milli seconds value" << aStartTime.value();
    if (mSoundVector_.length() > startTimeIndex)
    {
        mSoundVector_ = mSoundVector_.mid(0, startTimeIndex);
    }

    while (mSoundVector_.length() < startTimeIndex)
    {
        mSoundVector_.append(0);
    }

    QVector<double> appendDataVector(aSoundData.toVector());
    for(int index = 0; index < appendDataVector.length(); ++index)
    {
        mSoundVector_.append(appendDataVector.at(index));
    }
}

void SoundData::appendDataWithCrossfade(const SoundData &aSoundData,
                                        const MilliSeconds &aOverlapTime)
{
    updateInformationIfNotInitialized(aSoundData.soundDataInformation());
    int overlapArrayLength = mSoundDataInformation_.calculateIndex(aOverlapTime);

    for(int index = 0; index < aSoundData.toVector().length(); ++index)
    {
        if (index < overlapArrayLength - 1)
        {
            mSoundVector_[mSoundVector_.length() - 1 - index]
                  = mSoundVector_.at(mSoundVector_.length() - 1 - index)
                    * fadeOutFunction(index, overlapArrayLength)
                    + aSoundData.toVector().at(index) * fadeInFunction(index, overlapArrayLength);
            continue;
        }
        mSoundVector_.append(aSoundData.toVector().at(index));
    }
}

void SoundData::updateInformationIfNotInitialized(const SoundDataInformation& aSoundDataInformation)
{
    if (mSoundDataInformation_.isInitialized())
    {
        return;
    }
    mSoundDataInformation_ = aSoundDataInformation;
}

SoundDataInformation SoundData::soundDataInformation() const
{
    return mSoundDataInformation_;
}

void SoundData::pitchShift(const ScoreComponent::PitchCurve& /*aPitchCurve*/)
{
    WorldParameters worldParameters = {0};
    mSoundDataInformation_.setWorldParametersToValues(&worldParameters);

    worldParameters.framePeriod = 0.5;

    int samplingFrequency = worldParameters.samplingFrequency;
    int inputLengh = mSoundVector_.size();
    double *input = new double[inputLengh];

    for (int index = 0; index < inputLengh; ++index)
    {
        input[index] = mSoundVector_.at(index);
    }

    Synthesizer::getInstance().estimateF0(input,
                                          inputLengh,
                                          &worldParameters);
    Synthesizer::getInstance().SpectralEnvelopeEstimation(input,
                                                          inputLengh,
                                                          &worldParameters);
    Synthesizer::getInstance().AperiodicityEstimation(input,
                                                      inputLengh,
                                                      &worldParameters);
    // pitchshift

    int lengthOfOutput = static_cast<int>((worldParameters.lengthOfF0 - 1) *
      worldParameters.framePeriod / 1000.0 * samplingFrequency) + 1;
    double* output = new double[lengthOfOutput];

    Synthesizer::getInstance().WaveformSynthesis(&worldParameters,
                                                 samplingFrequency,
                                                 inputLengh,
                                                 output);
    mSoundVector_.clear();
    for (int index = 0; index < lengthOfOutput; ++index)
    {
        mSoundVector_.append(output[index]);
    }
    delete output;
    delete input;
}
