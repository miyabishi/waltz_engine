#ifndef MILLISECONDS_H
#define MILLISECONDS_H

#include "src/Domain/SoundPlayer/samplerate.h"
#include "src/Domain/SoundPlayer/samplesize.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class MilliSeconds
            {
            public:
                MilliSeconds();
                explicit MilliSeconds(const double aMilliSeconds);
                MilliSeconds(const MilliSeconds& aOther);
                MilliSeconds& operator=(const MilliSeconds& aOther);

                MilliSeconds add(const MilliSeconds& aOther) const;
                MilliSeconds subtract(const MilliSeconds& aOther) const;

                static MilliSeconds fromSeconds(const double aSeconds);

                double value() const;
                double toSeconds() const;
                int    toArrayLength(const waltz::engine::SoundPlayer::SampleRate& aSampleRate) const;
                int    toBitPosition(const waltz::engine::SoundPlayer::SampleRate& aSampleRate,
                                     const waltz::engine::SoundPlayer::SampleSize& aSampleSize) const;
                int toF0ArrayLength() const;

            private:
                double mMilliSeconds_;
            };
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // MILLISECONDS_H
