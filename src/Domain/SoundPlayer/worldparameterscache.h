#ifndef WORLDPARAMETERSCACHE_H
#define WORLDPARAMETERSCACHE_H

#include <QVector>
#include <QSharedPointer>
#include <QJsonObject>
#include "worldparameters.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class WorldParametersCache
            {
            public:
                explicit WorldParametersCache(WorldParameters* aWorldParameters);
                explicit WorldParametersCache(const QJsonObject& aWorldParameterData);
                void createWorldParameters(WorldParameters* aWorldParameters);

            public:
                QJsonObject toJsonObject() const;

            private:
                double mFramePeriod_;
                int mSamplingFrequency_;

                QVector<double> mF0_;
                QVector<double> mTimeAxis_;

                QVector<QVector<double>> mSpectrogram_;
                QVector<QVector<double>> mAperiodicity_;
                int mSizeOfFFT_;

            private:
                WorldParametersCache(const WorldParametersCache& aOther);
                WorldParametersCache& operator=(const WorldParametersCache& aOther) const;

            };
            typedef QSharedPointer<WorldParametersCache> WorldParametersCachePointer;

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // WORLDPARAMETERSCACHE_H
