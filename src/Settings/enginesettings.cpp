#include "enginesettings.h"
#include <QString>
#include <QFileInfo>

using namespace waltz::engine::Settings;

EngineSettings* EngineSettings::mInstance_ = 0;

namespace
{
    const double FRAME_PERIOD = 0.5; // ms
    const double PARAMETER_RESOLUTION = 1.0; // ms
    const QString DEFAULT_VOICE_LIBRARY_PATH = "./momo/momo.wvocal";
}

EngineSettings& EngineSettings::getInstance()
{
    if (mInstance_ == 0)
    {
        static EngineSettings instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

double EngineSettings::framePeriod() const
{
    return FRAME_PERIOD;
}

double EngineSettings::parameterResolution() const
{
    return PARAMETER_RESOLUTION;
}

QString EngineSettings::defaultVoiceLibraryPath() const
{
    QFileInfo info(DEFAULT_VOICE_LIBRARY_PATH);
    return info.absoluteFilePath();
}

EngineSettings::EngineSettings()
{
}
