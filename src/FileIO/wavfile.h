#ifndef WAVFILE_H
#define WAVFILE_H

#include <QString>
#include <QSharedPointer>
#include "src/Domain/SoundPlayer/sounddata.h"

namespace waltz
{
    namespace engine
    {
        namespace FileIO
        {
            class WavFile
            {
            public:
                WavFile(const QString& aFilePath);
                void write(SoundPlayer::SoundDataPointer aSoundData);

            private:
                QString mFilePath_;

            };
            typedef QSharedPointer<WavFile> WavFilePointer;

        } // namespace FileIO
    } // namespace engine
} // namespace waltz

#endif // WAVFILE_H
