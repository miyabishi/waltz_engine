#include <QDebug>
#include <waltzvocalagent.h>
#include <length.h>
#include <QVector>
#include "pitchcurve.h"
#include "phrase.h"
#include "alias.h"
#include "src/Domain/VocalComponent/vocal.h"

using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;
using namespace waltz::engine::VocalComponent;
using namespace waltz::agent;

Phrase::Phrase(const Notes& aNotes)
    : mNotes_(aNotes)
{
}

Phrase::~Phrase()
{
}

Phrase::Phrase(const Phrase& aOther)
    : mNotes_(aOther.mNotes_)
{
}

Phrase& Phrase::operator=(const Phrase& aOther)
{
    mNotes_ = aOther.mNotes_;
    return (*this);
}

std::vector<waltz::agent::IAlias*> Phrase::aliases() const
{
    return mNotes_.aliases().toStdVector();
}

SoundData Phrase::toSoundData() const
{
    WaltzVocalAgent* agent = Vocal::getInstance().vocalAgent();
    if (agent == 0)
    {
        return SoundData();
    }

    FragmentList fragmentList = agent->phraseToFragmentList(this);
    FragmentData firstData = fragmentList.at(0).at(0);
    SampleSize sampleSize = SampleSize(firstData.sampleSize());
    SampleRate sampleRate = SampleRate(firstData.sampleRate());

    SoundData soundData(QByteArray(firstData.waveformRawData(),
                                   firstData.waveformRawDataSize()),
                        SoundDataInformation(sampleSize, sampleRate));

    // 伸縮
    // 結合
    /*
    for(int index = 1; index < fragmentList.length(); ++index)
    {
        FragmentData data = fragmentList.at(index).at(0);
        soundData.appendDataWithCrossfade(
                    SoundData(QByteArray(data.waveformRawData(),
                                         data.waveformRawDataSize()),
                              sampleSize,
                              sampleRate),
                    MilliSeconds(data.overlap().asMilliSeconds()));
    }
    */

    // todo: ピッチ変換
    soundData.pitchShift(mNotes_.getPitchCurve());

    qDebug() << Q_FUNC_INFO << "to sound data";
    return soundData;
}

PhraseStartTime Phrase::phraseStartTime() const
{
    return PhraseStartTime(mNotes_.startTime());
}

PhraseLength Phrase::phraseLength() const
{
    return PhraseLength(mNotes_.length());
}

MilliSeconds Phrase::endTime() const
{
    return MilliSeconds(phraseStartTime().toMilliSeconds().value()
                        + phraseLength().toMilliSeconds().value());
}
