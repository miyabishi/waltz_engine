#ifndef SAMPLESIZE_H
#define SAMPLESIZE_H

#include <QAudioFormat>

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class SampleSize
            {
            public:
                SampleSize();
                SampleSize(const int aSampleSize);
                SampleSize(const SampleSize& aOther);
                SampleSize& operator=(const SampleSize& aOther);

            public:
                int value() const;
                QAudioFormat::SampleType sampleType() const;
                bool isInitialized() const;

            private:
                int mSampleSize_;
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SAMPLESIZE_H
