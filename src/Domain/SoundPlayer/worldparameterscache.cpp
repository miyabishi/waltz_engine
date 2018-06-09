#include <QJsonDocument>
#include <QJsonArray>
#include "worldparameterscache.h"

using namespace waltz::engine::SoundPlayer;

namespace
{
    QVector<double> createVector(double* aArray, int aLength)
    {
        QVector<double> result;
        for(int index = 0; index < aLength; ++index)
        {
            result.append(aArray[index]);
        }
        return result;
    }

    QVector<QVector<double>> create2DVector(double** a2DArray, int aX, int aY)
    {
        QVector<QVector<double>> result;
        for(int indexForX = 0; indexForX < aX; ++indexForX)
        {
            QVector<double> valueY;
            for(int indexForY = 0; indexForY < aY; ++indexForY)
            {
                valueY.append(a2DArray[indexForX][indexForY]);
            }
            result.append(valueY);
        }
        return result;
    }

    double* createArray(const QVector<double>& aVector)
    {
        double* result = new double[aVector.length()];
        for(int index = 0; index < aVector.length(); ++index)
        {
            result[index] = aVector.at(index);
        }
        return result;
    }

    double** create2DArray(const QVector<QVector<double>>& aVector, int aX, int aY)
    {

        double** result = new double *[aX];
        for (int index = 0; index < aX ; ++index)
        {
            result[index] = new double[aY];
        }

        for(int indexForX = 0; indexForX < aX; ++indexForX)
        {
            for(int indexForY = 0; indexForY < aY; ++indexForY)
            {
                result[indexForX][indexForY] = aVector.at(indexForX).at(indexForY);
            }
        }
        return result;
    }

    QJsonArray createJsonArray(const QVector<double>& aVector)
    {
        QJsonArray ary;
        for(int index = 0; index < aVector.size(); ++index)
        {
            ary.append(aVector.value(index));
        }
        return ary;
    }
    QJsonArray create2DJsonArray(const QVector<QVector<double>>& aVector)
    {
        QJsonArray aryRow;
        for(int indexForX = 0; indexForX < aVector.size(); ++indexForX)
        {
            QJsonArray aryColumn;
            for(int indexForY = 0; indexForY < aVector.at(indexForX).size(); ++indexForY)
            {
                aryColumn.append(aVector.at(indexForX).at(indexForY));
            }
            aryRow.append(aryColumn);
        }
        return aryRow;
    }
    double dataToDouble(const QJsonObject& aData, const QString& aKey)
    {
        QJsonValue value = aData.find(aKey).value();
        return value.toDouble();
    }
    QVector<double> createVectorFromData(const QJsonObject& aData, const QString& aKey)
    {
        QVector<double> ret;
        QJsonValue value = aData.find(aKey).value();
        foreach (const QJsonValue& v,value.toArray())
        {
            ret.append(v.toDouble());
        }
        return ret;
    }

    QVector<QVector<double>> create2DVectorFromData(const QJsonObject& aData, const QString& aKey)
    {
        QVector<QVector<double>> ret;
        QJsonValue value = aData.find(aKey).value();
        for(int index = 0; index < aData.size(); ++index)
        {
            QJsonArray ary = value.toArray();
            foreach (const QJsonValue& v, ary[index].toArray())
            {
                ret[index].append(v.toDouble());
            }
        }
        return ret;
    }

    const QString KEY_FRAME_PERIOD("FramePeriod");
    const QString KEY_SAMPLING_FREQUENCY("SamplingFrequency");
    const QString KEY_F0("F0");
    const QString KEY_TIME_AXIS("TimeAxis");
    const QString KEY_SPECTROGRAM("Spectrogram");
    const QString KEY_APERIODICITY("Aperiodicity");
    const QString KEY_SIZE_OF_FFT("SizeOfFFT");

}


WorldParametersCache::WorldParametersCache(WorldParameters* aWorldParameters)
    : mFramePeriod_(aWorldParameters->framePeriod)
    , mSamplingFrequency_(aWorldParameters->samplingFrequency)
    , mF0_(createVector(aWorldParameters->f0, aWorldParameters->lengthOfF0))
    , mTimeAxis_(createVector(aWorldParameters->timeAxis, aWorldParameters->lengthOfF0))
    , mSpectrogram_(create2DVector(aWorldParameters->spectrogram,
                                   aWorldParameters->lengthOfF0,
                                   aWorldParameters->sizeOfFFT / 2 +1))
    , mAperiodicity_(create2DVector(aWorldParameters->aperiodicity,
                                    aWorldParameters->lengthOfF0,
                                    aWorldParameters->sizeOfFFT / 2 +1))
    , mSizeOfFFT_(aWorldParameters->sizeOfFFT)
{
}

WorldParametersCache::WorldParametersCache(const QJsonObject& aWorldParameterData)
    : mFramePeriod_(dataToDouble(aWorldParameterData, KEY_FRAME_PERIOD))
    , mSamplingFrequency_(dataToDouble(aWorldParameterData, KEY_SAMPLING_FREQUENCY))
    , mF0_(createVectorFromData(aWorldParameterData, KEY_F0))
    , mTimeAxis_(createVectorFromData(aWorldParameterData, KEY_TIME_AXIS))
    , mSpectrogram_(create2DVectorFromData(aWorldParameterData, KEY_SPECTROGRAM))
    , mAperiodicity_(create2DVectorFromData(aWorldParameterData, KEY_APERIODICITY))
    , mSizeOfFFT_(dataToDouble(aWorldParameterData, KEY_SIZE_OF_FFT))
{
}

void WorldParametersCache::createWorldParameters(WorldParameters* aWorldParameters)
{
    aWorldParameters->framePeriod = mFramePeriod_;
    aWorldParameters->samplingFrequency = mSamplingFrequency_;
    aWorldParameters->f0 = createArray(mF0_);
    aWorldParameters->lengthOfF0 = mF0_.length();
    aWorldParameters->timeAxis = createArray(mTimeAxis_);
    aWorldParameters->spectrogram = create2DArray(mSpectrogram_,
                                                  mF0_.length(),
                                                  mSizeOfFFT_ / 2 + 1);
    aWorldParameters->aperiodicity = create2DArray(mAperiodicity_,
                                                   mF0_.length(),
                                                   mSizeOfFFT_ / 2 + 1);
    aWorldParameters->sizeOfFFT = mSizeOfFFT_;
}

QJsonObject WorldParametersCache::toJsonObject() const
{
    QJsonObject jsonObject;

    jsonObject[KEY_FRAME_PERIOD] = mFramePeriod_;
    jsonObject[KEY_SAMPLING_FREQUENCY] = mSamplingFrequency_;
    jsonObject[KEY_F0] = createJsonArray(mF0_);
    jsonObject[KEY_TIME_AXIS] = createJsonArray(mTimeAxis_);
    jsonObject[KEY_SPECTROGRAM] = create2DJsonArray(mSpectrogram_);
    jsonObject[KEY_APERIODICITY] = create2DJsonArray(mAperiodicity_);
    jsonObject[KEY_SIZE_OF_FFT] = mSizeOfFFT_;

    return jsonObject;
}
