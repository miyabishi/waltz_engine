#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T19:42:51
#
#-------------------------------------------------

QT       += core gui websockets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WaltzEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    src/Dialog/InformationDialog/informationdialog.cpp \
    src/Domain/Commands/commandfactory.cpp \
    src/Domain/Commands/loadvoicelibrarycommand.cpp \
    src/Domain/VocalComponent/vocal.cpp \
    src/Notifier/tasktraynotifier.cpp \
    src/Communicator/communicationserver.cpp \
    src/Communicator/receiveddata.cpp \
    src/Domain/Commands/playnotecommand.cpp \
    src/Domain/ScoreComponent/note.cpp \
    src/Domain/ScoreComponent/tone.cpp \
    src/Domain/ScoreComponent/octave.cpp \
    src/Domain/ScoreComponent/notestarttime.cpp \
    src/Domain/ScoreComponent/notelength.cpp \
    src/Domain/ScoreComponent/alias.cpp \
    src/Domain/SoundPlayer/player.cpp \
    src/Domain/ScoreComponent/phrase.cpp \
    src/Domain/ScoreComponent/score.cpp \
    src/Domain/ScoreComponent/notes.cpp \
    src/Domain/ScoreComponent/phrases.cpp \
    src/Domain/ScoreComponent/phrasestarttime.cpp \
    src/Domain/ScoreComponent/milliseconds.cpp \
    src/Domain/SoundPlayer/sounddata.cpp \
    src/Domain/ScoreComponent/phraselength.cpp \
    src/Domain/SoundPlayer/synthesizer.cpp \
    src/Domain/ScoreComponent/pitchcurve.cpp \
    src/Domain/SoundPlayer/sounddatainformation.cpp \
    src/Domain/SoundPlayer/samplesize.cpp \
    src/Domain/SoundPlayer/samplerate.cpp \
    world/cheaptrick.cpp \
    world/codec.cpp \
    world/common.cpp \
    world/d4c.cpp \
    world/dio.cpp \
    world/fft.cpp \
    world/harvest.cpp \
    world/matlabfunctions.cpp \
    world/stonemask.cpp \
    world/synthesis.cpp \
    world/synthesisrealtime.cpp \
    src/Settings/enginesettings.cpp \
    src/Domain/SoundPlayer/stretchinformation.cpp \
    src/Domain/SoundPlayer/fixedrange.cpp \
    src/Domain/Commands/playscorecommand.cpp \
    src/Domain/SoundPlayer/worldparametersrepository.cpp \
    src/Domain/ScoreComponent/pitchchangingpoint.cpp \
    src/Domain/ScoreComponent/timerange.cpp \
    src/Domain/SoundPlayer/worldparameterscache.cpp \
    src/Domain/SoundPlayer/worldparameterscacheid.cpp \
    src/FileIO/wavfile.cpp \
    src/Domain/Commands/savewavcommand.cpp \
    src/Domain/ScoreComponent/notevolume.cpp \
    src/Domain/ScoreComponent/vibrato.cpp \
    src/Domain/ScoreComponent/vibratoamplitude.cpp \
    src/Domain/ScoreComponent/vibratolength.cpp \
    src/Domain/ScoreComponent/vibratowavelength.cpp \
    src/Domain/ScoreComponent/vibratostarttime.cpp \
    src/Domain/Commands/stopcommand.cpp \
    src/Domain/VocalComponent/correspondencealias.cpp \
    src/Domain/VocalComponent/correspondencealiaslist.cpp \
    src/Domain/Commands/exitcommand.cpp

HEADERS  += \
    src/Dialog/InformationDialog/informationdialog.h \
    src/Domain/Commands/commandfactory.h \
    src/Domain/Commands/loadvoicelibrarycommand.h \
    src/Domain/VocalComponent/vocal.h \
    src/Notifier/tasktraynotifier.h \
    src/Communicator/communicationserver.h \
    src/Communicator/receiveddata.h \
    src/Domain/Commands/playnotecommand.h \
    src/Domain/ScoreComponent/note.h \
    src/Domain/ScoreComponent/tone.h \
    src/Domain/ScoreComponent/octave.h \
    src/Domain/ScoreComponent/notestarttime.h \
    src/Domain/ScoreComponent/notelength.h \
    src/Domain/ScoreComponent/alias.h \
    src/Domain/SoundPlayer/player.h \
    src/Domain/ScoreComponent/phrase.h \
    src/Domain/ScoreComponent/score.h \
    src/Domain/ScoreComponent/notes.h \
    src/Domain/ScoreComponent/phrases.h \
    src/Domain/ScoreComponent/phrasestarttime.h \
    src/Domain/ScoreComponent/milliseconds.h \
    src/Domain/SoundPlayer/sounddata.h \
    src/Domain/ScoreComponent/phraselength.h \
    src/Domain/SoundPlayer/synthesizer.h \
    src/Domain/ScoreComponent/pitchcurve.h \
    src/Domain/SoundPlayer/sounddatainformation.h \
    src/Domain/SoundPlayer/samplesize.h \
    src/Domain/SoundPlayer/samplerate.h \
    src/Domain/ScoreComponent/scoredef.h \
    world/cheaptrick.h \
    world/codec.h \
    world/common.h \
    world/constantnumbers.h \
    world/d4c.h \
    world/dio.h \
    world/fft.h \
    world/harvest.h \
    world/macrodefinitions.h \
    world/matlabfunctions.h \
    world/stonemask.h \
    world/synthesis.h \
    world/synthesisrealtime.h \
    src/Settings/enginesettings.h \
    src/Domain/SoundPlayer/stretchinformation.h \
    src/Domain/SoundPlayer/fixedrange.h \
    src/Domain/Commands/playscorecommand.h \
    src/Domain/SoundPlayer/worldparametersrepository.h \
    src/Domain/ScoreComponent/pitchchangingpoint.h \
    src/Domain/ScoreComponent/timerange.h \
    src/Domain/SoundPlayer/worldparameters.h \
    src/Domain/SoundPlayer/worldparameterscache.h \
    src/Domain/SoundPlayer/worldparameterscacheid.h \
    src/FileIO/wavfile.h \
    src/Domain/Commands/savewavcommand.h \
    src/Domain/ScoreComponent/notevolume.h \
    src/Domain/ScoreComponent/vibrato.h \
    src/Domain/ScoreComponent/vibratoamplitude.h \
    src/Domain/ScoreComponent/vibratolength.h \
    src/Domain/ScoreComponent/vibratowavelength.h \
    src/Domain/ScoreComponent/vibratostarttime.h \
    src/Domain/Commands/stopcommand.h \
    src/Domain/VocalComponent/correspondencealias.h \
    src/Domain/VocalComponent/correspondencealiaslist.h \
    src/Domain/Commands/exitcommand.h

RESOURCES += \
    resource/waltzengine.qrc

DISTFILES +=

# lib waltz vocal agent
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../WaltzVocalAgent/release/ -lWaltzVocalAgent
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../WaltzVocalAgent/debug/ -lWaltzVocalAgent
else:unix: LIBS += -L$$PWD/../WaltzVocalAgent/ -lWaltzVocalAgent

INCLUDEPATH += $$PWD/../WaltzVocalAgent/include
DEPENDPATH += $$PWD/../WaltzVocalAgent/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../WaltzCommonLibrary/release/ -lWaltzCommonLibrary
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../WaltzCommonLibrary/debug/ -lWaltzCommonLibrary
else:unix: LIBS += -L$$PWD/../WaltzCommonLibrary/ -lWaltzCommonLibrary

INCLUDEPATH += $$PWD/../WaltzCommonLibrary/include
DEPENDPATH += $$PWD/../WaltzCommonLibrary/include
