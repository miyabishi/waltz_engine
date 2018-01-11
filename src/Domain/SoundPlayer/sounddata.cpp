#include <QDebug>
#include <memory>
#include <QTextStream>
#include <QDataStream>
#include <QBuffer>
#include <qmath.h>
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
        double position = (double) (aIndex) / aLength;
        return (wavData - aZeroLine) * (-cos(position * M_PI) + 1) / 2;
    }

    double fadeOutFunction(const double wavData,
                           const double aZeroLine,
                           const int aIndex,
                           const int aLength)
    {
        double position = (double) (aIndex) / aLength;
        return (wavData - aZeroLine) * (cos(position * M_PI) + 1) / 2;
    }

    void outputToFile(double* array, int length, const QString& aFileName)
    {
        QFile file(aFileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

        QTextStream out(&file);
        for(int index = 0; index < length; ++index)
        {
            out << QString("%1\t%2").arg(index).arg(array[index]) << "\n";
        }
        file.close();

    }

    double noizeGate(double aValue, double aThreshold)
    {
        double abs = qAbs(aValue);
        if (abs < aThreshold)
        {
            return aValue * (abs / aThreshold);
        }
        return aValue;
    }
}

SoundData::SoundData()
    : mSoundVector_()
    , mSoundDataInformation_()
{
}

SoundData::SoundData(QSharedPointer<QByteArray> aData,
                     SoundDataInformationPointer aSoundDataInformation)
    : mSoundVector_()
    , mSoundDataInformation_(aSoundDataInformation)
    , mData_(aData)
{
    initializeWavDataByByteArray();
}

SoundData::~SoundData()
{
}

void SoundData::initializeWavDataByByteArray()
{
    mSoundVector_.clear();
    int quantization_byte = mSoundDataInformation_->quantizationByte();
    double zero_line = mSoundDataInformation_->zeroLine();

    QDataStream stream(*mData_.data());
    stream.setByteOrder(QDataStream::LittleEndian);
    int lengthOfOutput = mData_->length() / quantization_byte;

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

QVector<double> SoundData::toVector() const
{
    return mSoundVector_;
}

void SoundData::appendData(QSharedPointer<SoundData> aSoundData, const MilliSeconds &aStartTime)
{
    updateInformationIfNotInitialized(aSoundData->soundDataInformation());
    int startTimeIndex = mSoundDataInformation_->calculateIndex(aStartTime);

    if (mSoundVector_.length() > startTimeIndex)
    {
        mSoundVector_ = mSoundVector_.mid(0, startTimeIndex);
    }

    while (mSoundVector_.length() < startTimeIndex)
    {
        mSoundVector_.append(0);
    }

    QVector<double> appendDataVector(aSoundData->toVector());
    for(int index = 0; index < appendDataVector.length(); ++index)
    {
        mSoundVector_.append(appendDataVector.at(index));
    }
}

// リファクタ対象
void SoundData::appendDataWithCrossfade(QSharedPointer<SoundData> aSoundData,
                                        const MilliSeconds &aStartTime,
                                        const MilliSeconds &aOverlapTime)
{
    updateInformationIfNotInitialized(aSoundData->soundDataInformation());
    int startTimeIndex = mSoundDataInformation_->calculateIndex(aStartTime);
    int overlapArrayLength = mSoundDataInformation_->calculateIndex(aOverlapTime);
    int baseSoundVectorLength = startTimeIndex + overlapArrayLength;

    shrinkSoundVectorIfLongerThan(baseSoundVectorLength);
    extendSoundVectorIfShorterThan(baseSoundVectorLength);

    for(int index = 0; index < aSoundData->toVector().length(); ++index)
    {
        if (index >= overlapArrayLength)
        {
            mSoundVector_.append(aSoundData->toVector().at(index));
            continue;
        }
        int offset = mSoundVector_.length() - 1 - overlapArrayLength;
        int currentSoundVectorIndex = offset + index;

        double baseData = fadeOutFunction(mSoundVector_.at(currentSoundVectorIndex),
                                          0,
                                          index,
                                          overlapArrayLength);

        double appendData = fadeInFunction(aSoundData->toVector().at(index),
                                           0,
                                           index,
                                           overlapArrayLength);

        mSoundVector_[currentSoundVectorIndex] = baseData + appendData;
    }
}

void SoundData::shrinkSoundVectorIfLongerThan(int aLength)
{
    if (mSoundVector_.length() > aLength)
    {
        qDebug() << Q_FUNC_INFO << "SHRINK!";
        mSoundVector_ = mSoundVector_.mid(0, aLength);
    }
}

void SoundData::extendSoundVectorIfShorterThan(int aLength)
{
    while (mSoundVector_.length() < aLength)
    {
        qDebug() << Q_FUNC_INFO << "EXTEND!";
        mSoundVector_.append(0);
    }
}

void SoundData::updateInformationIfNotInitialized(SoundDataInformationPointer aSoundDataInformation)
{
    if (! mSoundDataInformation_.isNull() && mSoundDataInformation_->isInitialized())
    {
        return;
    }
    mSoundDataInformation_ = aSoundDataInformation;
}

SoundDataInformationPointer SoundData::soundDataInformation() const
{
    return mSoundDataInformation_;
}

void SoundData::transform(const PitchCurvePointer aPitchCurve,
                          const NoteVolumePointer aNoteVolume,
                          const VibratoPointer aVibrato,
                          const TimeRange& aNoteTimeRange,
                          const MilliSeconds& aFixedRangeLength,
                          const WorldParametersCacheId& aWorldParametersCacheId)
{
    WorldParameters worldParameters = {0};
    mSoundDataInformation_->setWorldParametersToValues(&worldParameters);
    int samplingFrequency = worldParameters.samplingFrequency;
    int inputLengh = mSoundVector_.size();
    double *input = new double[inputLengh];

    for (int index = 0; index < inputLengh; ++ index)
    {
        input[index] = noizeGate(mSoundVector_.at(index), 0.05);
    }

    // WORLDパラメータの作成
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
    int outputLength = mSoundDataInformation_->calculateIndex(aNoteTimeRange.length());
    double stretchRate = (double)(outputLength) / inputLengh;
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
    double f0FlexibleRangeStretchRate =
            (double)(outputF0Length - fixedRangeF0Length) /
            (worldParameters.lengthOfF0 - fixedRangeF0Length);



    for(int timeIndex = 0; timeIndex < outputF0Length; ++timeIndex)
    {
        // initialize
        int paramArrayLength = worldParameters.sizeOfFFT / 2 + 1;
        outputWorldParameters.spectrogram[timeIndex] = new double[paramArrayLength];
        outputWorldParameters.aperiodicity[timeIndex] = new double[paramArrayLength];
        outputWorldParameters.timeAxis[timeIndex] = worldParameters.framePeriod * timeIndex / 1000.0;

        // pitch
        MilliSeconds pos = MilliSeconds(
                    (aNoteTimeRange.length().value() / outputWorldParameters.lengthOfF0)* timeIndex)
                    .add(aNoteTimeRange.startTime());
        outputWorldParameters.f0[timeIndex] =
                aVibrato->calculatePitch(aPitchCurve->calculateValue(pos), pos);

        int sourceTimeIndex = 0;
        // fixed range
        if (timeIndex < fixedRangeF0Length && timeIndex < worldParameters.lengthOfF0)
        {
            sourceTimeIndex = timeIndex;
        }
        else
        {
            sourceTimeIndex = (double)(timeIndex) / f0FlexibleRangeStretchRate
                              + fixedRangeF0Length - (double)(fixedRangeF0Length)/f0FlexibleRangeStretchRate;
        }

        //flexible range
        for(int arrayIndex = 0; arrayIndex < paramArrayLength; ++arrayIndex)
        {
            outputWorldParameters.spectrogram[timeIndex][arrayIndex] =
                    worldParameters.spectrogram[sourceTimeIndex][arrayIndex];
            outputWorldParameters.aperiodicity[timeIndex][arrayIndex] =
                    worldParameters.aperiodicity[sourceTimeIndex][arrayIndex];
        }
    }

    Synthesizer::getInstance().WaveformSynthesis(&outputWorldParameters,
                                                 samplingFrequency,
                                                 outputLength,
                                                 output);
    mSoundVector_.clear();
    for (int index = 0; index < outputLength; ++index)
    {
        mSoundVector_.append(aNoteVolume->calculateSoundValue((output[index])));
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
