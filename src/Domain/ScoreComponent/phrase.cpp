#include <QDebug>
#include <waltzvocalagent.h>
#include <length.h>
#include <QVector>
#include "pitchcurve.h"
#include "phrase.h"
#include "alias.h"
#include "src/Domain/VocalComponent/vocal.h"
#include "src/Domain/SoundPlayer/worldparameterscacheid.h"

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
    if (agent == 0 || mNotes_.length() == 0)
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

    NotePointer firstNote = mNotes_.at(0);
    // TODO WorldParametersCacheId を一意なものにすること
    soundData.pitchShift(mNotes_.getPitchCurve(),
                         TimeRange(
                             firstNote->noteStartTime().toMilliSeconds().subtract(
                                 MilliSeconds(firstData.overlap().asMilliSeconds())),
                             firstNote->endTime()),
                         WorldParametersCacheId(QString::fromStdString(firstData.phonemes())));
//    soundData.addFadeOut(MilliSeconds(100));

    // TODO
    if ( fragmentList.length() < mNotes_.length())
    {
        return SoundData();
    }
    // 伸縮
    // 結合 まだ mNotes_の数とfragmentの数が異なる場合には対応していない
    for(int index = 1; index < mNotes_.length(); ++index)
    {
        FragmentData data = fragmentList.at(index).at(0);
        SoundData fragmentSoundData(QByteArray(data.waveformRawData(),
                                               data.waveformRawDataSize()),
                                    SoundDataInformation(sampleSize, sampleRate));

        NotePointer note = mNotes_.at(index);
        fragmentSoundData.pitchShift(mNotes_.getPitchCurve(),
                                     TimeRange(
                                         note->noteStartTime().toMilliSeconds().subtract(
                                             MilliSeconds(data.overlap().asMilliSeconds())),
                                         note->endTime()),
                                     WorldParametersCacheId(QString::fromStdString(data.phonemes())));
//        soundData.addFadeOut(MilliSeconds(100));
        soundData.appendDataWithCrossfade(
                    fragmentSoundData,
                    note->noteStartTime().toMilliSeconds().subtract(mNotes_.startTime()),
                    MilliSeconds(data.overlap().asMilliSeconds()));
    }

    return soundData;
}

PhraseStartTime Phrase::phraseStartTime() const
{
    return PhraseStartTime(mNotes_.startTime());
}

PhraseLength Phrase::phraseLength() const
{
    return PhraseLength(mNotes_.timeLength());
}

MilliSeconds Phrase::endTime() const
{
    return MilliSeconds(phraseStartTime().toMilliSeconds().value()
                        + phraseLength().toMilliSeconds().value());
}
