#include <QDataStream>
#include <QDebug>
#include <waltz_common/parameters.h>
#include <waltz_common/parameter.h>
#include <waltz_common/message.h>
#include <fragmentlist.h>
#include <samephonemefragmentsets.h>

#include "src/Domain/ScoreComponent/note.h"
#include "src/Communicator/communicationserver.h"
#include "src/Domain/SoundPlayer/player.h"
#include "src/Domain/SoundPlayer/sounddatainformation.h"
#include "src/Domain/SoundPlayer/sounddata.h"

#include "src/Domain/ScoreComponent/phrase.h"
#include "src/Domain/ScoreComponent/notes.h"
#include "src/Domain/ScoreComponent/phrases.h"
#include "src/Domain/ScoreComponent/score.h"
#include "src/Domain/SoundPlayer/worldparametersrepository.h"

#include "correspondencealiaslist.h"
#include "vocal.h"

using namespace waltz::common::Commands;
using namespace waltz::common::Communicator;
using namespace waltz::agent;
using namespace waltz::engine::VocalComponent;
using namespace waltz::engine::Communicator;
using namespace waltz::engine::ScoreComponent;
using namespace waltz::engine::SoundPlayer;

namespace
{
    const CommandId COMMAND_ID_UPDATE_LIBRARY_INFORMATION("UpdateLibraryInformation");
}

Vocal* Vocal::mInstance_ = 0;

Vocal& Vocal::getInstance()
{
    if(mInstance_ == 0)
    {
        static Vocal instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

void Vocal::loadVoiceLibrary(const QString &aPath)
{
    mVocalAgent_.loadVocal(aPath.toStdString());

    if (! WorldParametersRepository::getInstance().open(aPath + ".db"))
    {
        qDebug() << "failed to open." << (aPath + ".db");
    }
    else
    {
        qDebug() << "success to open";
    }

//    registerAllWorldParametersCache();

    Parameters parameters;
    parameters.append(Parameter("ImageFilePath",
                          QString::fromStdString(mVocalAgent_.characterImageFilePath())));
    parameters.append(Parameter("Description",
                          QString::fromStdString(mVocalAgent_.characterDescription())));
    parameters.append(Parameter("LibraryName",
                                QString::fromStdString(mVocalAgent_.libraryName())));
    parameters.append(Parameter("LibraryFilePath", aPath));


    CorrespondenceAliasListPointer correspondenceAliasList(
                new CorrespondenceAliasList(mVocalAgent_.correspondenceAliasVector()));

    parameters.append(correspondenceAliasList->toParameter());


    CommunicationServer::getInstance().sendMessage(
                Message(COMMAND_ID_UPDATE_LIBRARY_INFORMATION,
                        parameters));
}


void Vocal::registerAllWorldParametersCache() const
{
    FragmentList list = mVocalAgent_.allFragmentList();

    for(int fragmentIndex = 0; fragmentIndex < list.length(); ++fragmentIndex)
    {
        SamePhonemeFragmentSets fragmentSets = list.at(fragmentIndex);
        for (int setIndex = 0; setIndex < fragmentSets.length(); ++setIndex)
        {
            FragmentData data = fragmentSets.at(setIndex);
            WorldParametersCacheId cacheId(QString::fromStdString(data.phonemes()));
            if (WorldParametersRepository::getInstance().hasWorldParammeters(cacheId)) continue;
            SoundDataPointer soundData = SoundData::fromFragmentData(data);
            soundData->registerToWorldParameterRepository(cacheId);
        }
    }
}

void Vocal::singSingleNote(const Note& /*aNote*/)
{
    /*
    if (! mVocalAgent_.isLibraryLoaded())
    {
        return;
    }
    NotePointer temporaryNote(new Note(aNote));
    temporaryNote->moveToTop();
    Notes notes;
    notes.append(temporaryNote);
    Phrase phrase(notes);
    SoundDataPointer soundData = phrase.toSoundData(
                PitchCurvePointer(new PitchCurve()));
    mPlayer_.start(soundData);
    */
}

void Vocal::sing(const Score &aScore,
                 const waltz::engine::ScoreComponent::MilliSeconds& aStartPosition)
{
    if(! mVocalAgent_.isLibraryLoaded()) return;

    mPlayer_.start(aScore.toSoundData(), aStartPosition);
}

void Vocal::stopSinging()
{
    mPlayer_.stop();
}

waltz::agent::WaltzVocalAgent* Vocal::vocalAgent()
{
    return &mVocalAgent_;
}


Vocal::Vocal()
 : mVocalAgent_()
 , mPlayer_()
{
}
