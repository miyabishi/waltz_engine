#ifndef SOUNDDATAINFORMATION_H
#define SOUNDDATAINFORMATION_H

#include <QAudioFormat>
#include <QByteArray>
#include <QSharedPointer>
#include "samplerate.h"
#include "samplesize.h"
#include "synthesizer.h"
#include "src/Domain/ScoreComponent/milliseconds.h"



namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            class SoundDataInformation
            {
            public:
                SoundDataInformation();
                SoundDataInformation(const SampleSize& aSampleSize,
                                     const SampleRate& aSampleRate);
                SoundDataInformation(const SoundDataInformation& aOther);
                SoundDataInformation& operator=(const SoundDataInformation& aOther);

            public:
                QAudioFormat createAudioFormat();
                bool isInitialized() const;
                int  quantizationByte() const;
                double zeroLine() const;
                int calculateIndex(waltz::engine::ScoreComponent::MilliSeconds aMilliSeconds);
                void setWorldParametersToValues(WorldParameters* aWorldParameters);

            private:
                SampleSize mSampleSize_;
                SampleRate mSampleRate_;
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SOUNDDATAINFORMATION_H
