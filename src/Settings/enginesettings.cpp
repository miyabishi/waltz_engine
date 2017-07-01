#include "enginesettings.h"

using namespace waltz::engine::Settings;

EngineSettings* EngineSettings::mInstance_ = 0;

namespace
{
    const double FRAME_PERIOD = 0.2; // ms
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

EngineSettings::EngineSettings()
{

}
