#include <QDebug>
#include <memory>
#include <QDataStream>
#include <QBuffer>
#include "worldparametersrepository.h"
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

    double fadeInFunction(const double wavData,
                          const double aZeroLine,
                          const int aIndex,
                          const int aLength)
    {
        return (wavData - aZeroLine) * linearFunction(aIndex,
                                                      aLength,
                                                      0,
                                                      1)
                + aZeroLine;
    }

    double fadeOutFunction(const double wavData,
                           const double aZeroLine,
                           const int aIndex,
                           const int aLength)
    {
        return (wavData - aZeroLine) * linearFunction(aIndex,
                                                     aLength,
                                                     1,
                                                     0)
               + aZeroLine;
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
    outputWaveDataForDebug("initial_output.txt");
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
                                        const MilliSeconds& aStartTime,
                                        const MilliSeconds &aOverlapTime)
{
    updateInformationIfNotInitialized(aSoundData.soundDataInformation());
    int startTimeIndex = mSoundDataInformation_.calculateIndex(aStartTime);
    int overlapArrayLength = mSoundDataInformation_.calculateIndex(aOverlapTime);

    if (mSoundVector_.length() > startTimeIndex)
    {
        mSoundVector_ = mSoundVector_.mid(0, startTimeIndex);
    }

    for(int index = 0; index < aSoundData.toVector().length(); ++index)
    {
        if (index < overlapArrayLength - 1)
        {
            double baseData = fadeOutFunction(mSoundVector_.at(mSoundVector_.length() - 1 - index),
                                              0,
                                              index,
                                              overlapArrayLength);
            double appendData = fadeInFunction(mSoundVector_.at(mSoundVector_.length() - 1 - index),
                                               0,
                                               index,
                                               overlapArrayLength);

            mSoundVector_[mSoundVector_.length() - 1 - index]
                  = baseData + appendData;
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

void SoundData::transform(const ScoreComponent::PitchCurvePointer aPitchCurve,
                          const ScoreComponent::TimeRange& aNoteTimeRange,
                          const ScoreComponent::MilliSeconds& aFixedRangeLength,
                          const WorldParametersCacheId& aWorldParametersCacheId)
{
    WorldParameters worldParameters = {0};
    mSoundDataInformation_.setWorldParametersToValues(&worldParameters);
    int samplingFrequency = worldParameters.samplingFrequency;
    int inputLengh = mSoundVector_.size();
    double *input = new double[inputLengh];

    for (int index = 0; index < inputLengh; ++ index)
    {
        input[index] = mSoundVector_.at(index);
    }

    // WORLパラメータの作成
    if(WorldParametersRepository::getInstance().hasWorldParammeters(aWorldParametersCacheId))
    {
        WorldParametersRepository::getInstance().loadWorldParameters(aWorldParametersCacheId,
                                                                     &worldParameters);
    }
    else
    {
        Synthesizer::getInstance().estimateF0(input,
                                              inputLengh,
                                              &worldParameters);

        Synthesizer::getInstance().SpectralEnvelopeEstimation(input,
                                                              inputLengh,
                                                              &worldParameters);
        Synthesizer::getInstance().AperiodicityEstimation(input,
                                                          inputLengh,
                                                          &worldParameters);
        WorldParametersRepository::getInstance().registerWorldParameters(aWorldParametersCacheId,
                                                                        &worldParameters);
    }
    // 伸縮
    int outputLength = mSoundDataInformation_.calculateIndex(aNoteTimeRange.length());
    double stretchRate = (double)outputLength / inputLengh;
    double* output = new double[outputLength];

    WorldParameters outputWorldParameters = {0};
    int outputF0Length = int(worldParameters.lengthOfF0 * stretchRate);
    outputWorldParameters.lengthOfF0 = outputF0Length;
    outputWorldParameters.framePeriod = worldParameters.framePeriod;
    outputWorldParameters.samplingFrequency = worldParameters.samplingFrequency;
    outputWorldParameters.sizeOfFFT = worldParameters.sizeOfFFT;
    outputWorldParameters.f0 = new double[outputF0Length];
    outputWorldParameters.timeAxis = new double[outputF0Length];
    outputWorldParameters.spectrogram = new double *[outputF0Length];
    outputWorldParameters.aperiodicity = new double *[outputF0Length];
    int fixedRangeF0Length = aFixedRangeLength.toF0ArrayLength();

    qDebug() << "source length of f0:" << worldParameters.lengthOfF0;
    qDebug() << "input length:" << inputLengh;
    qDebug() << "output length of f0:" << outputWorldParameters.lengthOfF0;
    qDebug() << "output length:" << outputLength;


    for(int timeIndex = 0; timeIndex < outputF0Length; ++timeIndex)
    {
        // initialize
        int paramArrayLength = worldParameters.sizeOfFFT / 2 + 1;
        outputWorldParameters.spectrogram[timeIndex] = new double[paramArrayLength];
        outputWorldParameters.aperiodicity[timeIndex] = new double[paramArrayLength];
        outputWorldParameters.timeAxis[timeIndex] = worldParameters.framePeriod * timeIndex / 1000.0;

        // pitch
        MilliSeconds pos = MilliSeconds(outputWorldParameters.timeAxis[timeIndex]).add(aNoteTimeRange.startTime());
        outputWorldParameters.f0[timeIndex] = aPitchCurve->calculateValue(pos);

        // fixed range
        if (timeIndex < fixedRangeF0Length && timeIndex < worldParameters.lengthOfF0)
        {
            for(int arrayIndex = 0; arrayIndex < paramArrayLength; ++arrayIndex)
            {
                outputWorldParameters.spectrogram[timeIndex][arrayIndex] =
                        worldParameters.spectrogram[timeIndex][arrayIndex];
                outputWorldParameters.aperiodicity[timeIndex][arrayIndex] =
                        worldParameters.aperiodicity[timeIndex][arrayIndex];
            }
            continue;
        }

        //flexible range
        for(int arrayIndex = 0; arrayIndex < paramArrayLength; ++arrayIndex)
        {
            int sourceTimeIndex = (double)timeIndex / stretchRate;
            outputWorldParameters.spectrogram[timeIndex][arrayIndex] =
                    worldParameters.spectrogram[sourceTimeIndex][arrayIndex];
            outputWorldParameters.aperiodicity[timeIndex][arrayIndex] =
                    worldParameters.aperiodicity[sourceTimeIndex][arrayIndex];
        }
    }


    /*
    double* output = new double[inputLengh];

    // ピッチ変換
    for(int index = 0; index < worldParameters.lengthOfF0; ++index)
    {
        MilliSeconds pos = MilliSeconds((aNoteTimeRange.length().value() / worldParameters.lengthOfF0)* index).add(aNoteTimeRange.startTime());
        worldParameters.f0[index] = aPitchCurve->calculateValue(pos);
    }

    for(int index = 0; index < inputLengh; ++index)
    {
        output[index] = 0;
    }
    */
    Synthesizer::getInstance().WaveformSynthesis(&outputWorldParameters,
                                                 samplingFrequency,
                                                 outputLength,
                                                 output);
    mSoundVector_.clear();
    for (int index = 0; index < outputLength; ++index)
    {
        mSoundVector_.append(output[index]);
    }

    Synthesizer::getInstance().DestroyMemory(&worldParameters);
    Synthesizer::getInstance().DestroyMemory(&outputWorldParameters);
    delete output;
    delete input;
}

void SoundData::outputWaveDataForDebug(const QString& aFileName) const
{
    QFile file(aFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;

    QTextStream out(&file);
    for(int index = 0; index < mSoundVector_.length(); ++index)
    {
        out << QString("%1\t%2").arg(index).arg(mSoundVector_.at(index)) << "\n";
    }
    file.close();
}
