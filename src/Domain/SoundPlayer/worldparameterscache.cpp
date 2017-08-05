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
