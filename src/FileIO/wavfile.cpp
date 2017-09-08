#include <QByteArray>
#include <QFile>
#include <QAudioFormat>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include "wavfile.h"


using namespace waltz::engine::FileIO;
using namespace waltz::engine::SoundPlayer;

WavFile::WavFile(const QString& aFilePath)
    :mFilePath_(aFilePath)
{

}

void WavFile::write(SoundPlayer::SoundDataPointer aSoundData)
{
    qDebug() << Q_FUNC_INFO << __LINE__;
    SoundDataInformationPointer sounddataInformation = aSoundData->soundDataInformation();
    QAudioFormat format = sounddataInformation->createAudioFormat();
    QByteArray* rawData = new QByteArray(aSoundData->toByteArray());
    int rawDataSize = rawData->size();

    long chunksize=16;
    struct
    {
        unsigned short    wFormatTag;
        unsigned short    wChannels;
        unsigned long     dwSamplesPerSec;
        unsigned long     dwAvgBytesPerSec;
        unsigned short    wBlockAlign;
        unsigned short    wBitsPerSample;
    } fmt;

    long riffsize    = rawDataSize + 36;

    QFile wav(mFilePath_);
    wav.open(QFile::WriteOnly);

    wav.write("RIFF", 4);
    wav.write(reinterpret_cast<char*>(&riffsize),  4);
    wav.write("WAVE", 4);
    wav.write("fmt ", 4);
    wav.write(reinterpret_cast<char*>(&chunksize), 4);
    fmt.wFormatTag = 1;
    fmt.wChannels  = format.channelCount();
    fmt.dwSamplesPerSec  = format.sampleRate();
    fmt.dwAvgBytesPerSec = format.sampleRate() * format.channelCount() * (format.sampleSize()/8 ); // 16 bit
    fmt.wBlockAlign      = format.sampleSize() / 8 * format.channelCount();
    fmt.wBitsPerSample   = format.sampleSize();
    wav.write(reinterpret_cast<char*>(&fmt) ,sizeof(fmt));
    wav.write("data", 4);
    wav.write(reinterpret_cast<char*>(&rawDataSize), 4);
    wav.write(*rawData);
    wav.close();
    delete rawData;
}
