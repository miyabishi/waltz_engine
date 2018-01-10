#include "note.h"

using namespace waltz::engine::ScoreComponent;

namespace
{
    const QString PARAMETER_NAME_TONE_VALUE("ToneValue");
    const QString PARAMETER_NAME_TONE_OCTAVE("Octave");
    const QString PARAMETER_NAME_ALIAS("Alias");
    const QString PARAMETER_NAME_NOTE_START_TIME("NoteStartTime");
    const QString PARAMETER_NAME_NOTE_LENGTH("NoteLength");
    const QString PARAMETER_NAME_NOTE_VOLUME("NoteVolume");
    const QString PARAMETER_NAME_VIBRATO_LENGTH("VibratoLength");
    const QString PARAMETER_NAME_VIBRATO_WAVELENGTH("VibratoWavelength");
    const QString PARAMETER_NAME_VIBRATO_AMPLITUDE("VibratoAmplitude");
}

Note::Note(const waltz::common::Commands::Parameters& aParameters)
    : mTone_((ToneValue)aParameters.find(PARAMETER_NAME_TONE_VALUE).value().toInt(),
               aParameters.find(PARAMETER_NAME_TONE_OCTAVE).value().toInt())
    , mAlias_(* (new Alias(aParameters.find(PARAMETER_NAME_ALIAS).value().toString())))
    , mNoteStartTime_(MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_NOTE_START_TIME).value().toDouble()))
    , mNoteLength_(MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_NOTE_LENGTH).value().toDouble()))
    , mNoteVolume_(NoteVolumePointer(new NoteVolume(aParameters.find(PARAMETER_NAME_NOTE_VOLUME).value().toInt())))
    , mVibrato_(VibratoPointer(new Vibrato(
                                   VibratoLengthPointer(new VibratoLength(
                                                            MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_VIBRATO_LENGTH).value().toDouble()))),
                                   VibratoWavelengthPointer(new VibratoWavelength(
                                                            MilliSeconds::fromSeconds(aParameters.find(PARAMETER_NAME_VIBRATO_WAVELENGTH).value().toDouble()))),
                                   VibratoAmplitudePointer(new VibratoAmplitude(
                                                            aParameters.find(PARAMETER_NAME_VIBRATO_AMPLITUDE).value().toDouble())))))
{
}

Note::Note(const Tone& aTone,
           const Alias& aAlias,
           const NoteStartTime& aNoteStartTime,
           const NoteLength& aNoteLength)
    : mTone_(aTone)
    , mAlias_(*(new Alias(aAlias)))
    , mNoteStartTime_(aNoteStartTime)
    , mNoteLength_(aNoteLength)
{
}

Note::~Note()
{
    delete &mAlias_;
}
Alias* Note::alias() const
{
    return &mAlias_;
}

NoteLength Note::noteLength() const
{
    return mNoteLength_;
}

NoteVolumePointer Note::noteVolume() const
{
    return mNoteVolume_;
}

NoteStartTime Note::noteStartTime() const
{
    return mNoteStartTime_;
}

MilliSeconds Note::endTime() const
{
    double endTime;
    endTime = mNoteStartTime_.toMilliSeconds().value()
              + mNoteLength_.toMilliSeconds().value();
    return MilliSeconds(endTime);
}

void Note::moveToTop()
{
    mNoteStartTime_ = NoteStartTime(MilliSeconds(0.0));
}

Tone Note::tone() const
{
    return mTone_;
}

TimeRange Note::noteTimeRange() const
{
    return TimeRange(noteStartTime().toMilliSeconds(),
                     noteStartTime().toMilliSeconds().add(mNoteLength_.toMilliSeconds()));
}
