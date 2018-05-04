#ifndef SOUNDDATA_H
#define SOUNDDATA_H

#include <QByteArray>
#include <QVector>
#include <QSharedPointer>

#include "sounddatainformation.h"
#include "worldparameterscacheid.h"
#include "src/Domain/ScoreComponent/pitchcurve.h"
#include "src/Domain/ScoreComponent/milliseconds.h"
#include "src/Domain/ScoreComponent/timerange.h"
#include "src/Domain/ScoreComponent/notevolume.h"
#include "src/Domain/ScoreComponent/vibrato.h"

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
                SoundData(QSharedPointer<QByteArray> aData,
                          SoundDataInformationPointer aSoundDataInformation);

                ~SoundData();

            public:
                void appendData(QSharedPointer<SoundData> aSoundData,
                                const waltz::engine::ScoreComponent::MilliSeconds& aStartTime);
                void appendDataWithCrossfade(QSharedPointer<SoundData> aSoundData,
                                             const waltz::engine::ScoreComponent::MilliSeconds& aStartTime,
                                             const waltz::engine::ScoreComponent::MilliSeconds& aOverlapTime);
                void transform(const ScoreComponent::PitchCurvePointer aPitchCurve,
                               const ScoreComponent::NoteVolumePointer aNoteVolume,
                               const ScoreComponent::VibratoPointer aVibratoPointer,
                               const ScoreComponent::TimeRange& aNoteTimeRange,
                               const ScoreComponent::MilliSeconds& FixedRangeLength,
                               const WorldParametersCacheId& aWorldParametersCacheId);

                QVector<double> toVector() const;
                QByteArray toByteArray(const ScoreComponent::MilliSeconds& aStartTime = ScoreComponent::MilliSeconds(0.0)) const;
                SoundDataInformationPointer soundDataInformation() const;
                void outputWaveDataForDebug(const QString& aFileName) const;
                QSharedPointer<SoundData> rightSideFrom(const ScoreComponent::MilliSeconds& aStartTime) const;

            private:
                void updateInformationIfNotInitialized(SoundDataInformationPointer aSoundDataInformation);
                void initializeWavDataByByteArray();
                int16_t roudedSoundValue(int aIndex) const;
                void shrinkSoundVectorIfLongerThan(int aLength);
                void extendSoundVectorIfShorterThan(int aLength);

            private:
                QVector<double>             mSoundVector_;
                SoundDataInformationPointer mSoundDataInformation_;
                QSharedPointer<QByteArray>  mData_;

            private:
                SoundData(const SoundData& aOther);
                SoundData& operator=(const SoundData& aOther);
            };
            typedef QSharedPointer<SoundData> SoundDataPointer;

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SOUNDDATA_H
