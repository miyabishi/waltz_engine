#ifndef SAMPLERATE_H
#define SAMPLERATE_H


namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class SampleRate
            {
            public:
                SampleRate();
                SampleRate(const int aSampleRate);
                SampleRate(const SampleRate& aOther);
                SampleRate& operator=(const SampleRate &aOther);
            public:
                int value() const;
                bool isInitialized() const;

            private:
                int mSampleRate_;
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // SAMPLERATE_H
