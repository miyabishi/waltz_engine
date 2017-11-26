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
    , mPrecedingTime_(0)
{
}

Phrase::~Phrase()
{
}

Phrase::Phrase(const Phrase& aOther)
    : mNotes_(aOther.mNotes_)
    , mPrecedingTime_(aOther.mPrecedingTime_)
{
}

Phrase& Phrase::operator=(const Phrase& aOther)
{
    mNotes_ = aOther.mNotes_;
    mPrecedingTime_ = aOther.mPrecedingTime_;
    return (*this);
}

std::vector<waltz::agent::IAlias*> Phrase::aliases() const
{
    return mNotes_.aliases().toStdVector();
}

SoundDataPointer Phrase::toSoundData(const PitchCurvePointer aPitchCurve)
{
    WaltzVocalAgent* agent = Vocal::getInstance().vocalAgent();
    if (agent == 0 || mNotes_.length() == 0)
    {
        return SoundDataPointer();
    }

    FragmentList fragmentList = agent->phraseToFragmentList(this);
    if (fragmentList.length() == 0) return SoundDataPointer();

    FragmentData firstData = fragmentList.at(0).at(0);
    mPrecedingTime_ = MilliSeconds(firstData.preceding().asMilliSeconds());

    SampleSize sampleSize = SampleSize(firstData.sampleSize());
    SampleRate sampleRate = SampleRate(firstData.sampleRate());

    SoundDataInformationPointer soundDataInformation(
                new SoundDataInformation(sampleSize, sampleRate));

    SoundDataPointer soundData(
                new SoundData(QSharedPointer<QByteArray>(
                                  new QByteArray(firstData.waveformRawData(),
                                                 firstData.waveformRawDataSize())),
                               soundDataInformation));

    //PitchCurvePointer pitchCurve = mNotes_.getPitchCurve();

    NotePointer firstNote = mNotes_.at(0);

    // TODO WorldParametersCacheId を一意なものにすること
    soundData->transform(aPitchCurve,
                         TimeRange(firstNote->noteStartTime().toMilliSeconds()
                                   .subtract(MilliSeconds(firstData.preceding().asMilliSeconds())),
                                   firstNote->endTime()),
                         MilliSeconds(firstData.lengthOfFixedRange().asMilliSeconds()),
                         WorldParametersCacheId(QString::fromStdString(firstData.phonemes())));
    // TODO
    if ( fragmentList.length() < mNotes_.length())
    {
        return SoundDataPointer();
    }

    // TODO: 結合 まだ mNotes_の数とfragmentの数が異なる場合には対応していない
    for(int index = 1; index < mNotes_.length(); ++index)
    {
        FragmentData data = fragmentList.at(index).at(0);

        SoundDataPointer fragmentSoundData(
                    new SoundData(QSharedPointer<QByteArray>(
                                      new QByteArray(data.waveformRawData(),
                                                     data.waveformRawDataSize())),
                                  soundDataInformation));

        NotePointer note = mNotes_.at(index);
        MilliSeconds overlapTime = MilliSeconds(data.preceding().asMilliSeconds());
        MilliSeconds soundStartTime = note->noteStartTime().toMilliSeconds()
                                                           .subtract(overlapTime);
        MilliSeconds soundEndTime = note->endTime();
        MilliSeconds fixedRangeTime = MilliSeconds(data.lengthOfFixedRange().asMilliSeconds());

        fragmentSoundData->transform(aPitchCurve,
                                     TimeRange(soundStartTime,soundEndTime),
                                     fixedRangeTime,
                                     WorldParametersCacheId(QString::fromStdString(data.phonemes())));

        soundData->appendDataWithCrossfade(fragmentSoundData,
                                           soundStartTime.subtract(mNotes_.startTime()).add(mPrecedingTime_),
                                           overlapTime);
    }

    aPitchCurve->outputForDebug("pitchCurve_debug.txt");
    return soundData;
}
// ここのmPrecedingTime直したい。。。
PhraseStartTime Phrase::phraseStartTime() const
{
    return PhraseStartTime(mNotes_.startTime().subtract(mPrecedingTime_));
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
