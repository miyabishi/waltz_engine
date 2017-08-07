#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include <QByteArray>
#include <QVector>
#include "sounddatainformation.h"
#include "worldparameterscacheid.h"
#include "src/Domain/ScoreComponent/pitchcurve.h"
#include "src/Domain/ScoreComponent/milliseconds.h"
#include "src/Domain/ScoreComponent/timerange.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            class SoundData
            {
            public:
                SoundData();
                SoundData(const QByteArray& aData,
                          const SoundDataInformation& aSoundDataInformation);
                SoundData(const SoundData& aOther);
                SoundData& operator=(const SoundData& aOther);
                ~SoundData();

            public:
                void appendData(const SoundData& aSoundData,
                                const waltz::engine::ScoreComponent::MilliSeconds& aStartTime);
                void appendDataWithCrossfade(const SoundData& aSoundData,
                                             const waltz::engine::ScoreComponent::MilliSeconds& aStartTime,
                                             const waltz::engine::ScoreComponent::MilliSeconds& aOverlapTime);
                void stretch(const ScoreComponent::MilliSeconds& aStartTime);
                void pitchShift(const ScoreComponent::PitchCurvePointer aPitchCurve,
                                const ScoreComponent::TimeRange& aTimeRange,
                                const WorldParametersCacheId& aWorldParametersCacheId);

                QVector<double> toVector() const;
                QByteArray toByteArray() const;
                SoundDataInformation soundDataInformation() const;
                void outputWaveDataForDebug(const QString& aFileName) const;

            private:
                void updateInformationIfNotInitialized(const SoundDataInformation& aSoundDataInformation);
                void initializeWavDataByByteArray(const QByteArray& aByteArray);
                int16_t roudedSoundValue(int aIndex) const;

            private:
                QVector<double>      mSoundVector_;
                SoundDataInformation mSoundDataInformation_;
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SOUNDDATA_H
