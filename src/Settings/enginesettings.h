#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H


namespace waltz
{
    namespace engine
    {
        namespace Settings
        {

            class EngineSettings
            {
            public:
                static EngineSettings& getInstance();
                double framePeriod() const;
                double parameterResolution() const;
            private:
                static EngineSettings* mInstance_;
                EngineSettings();

            };

        } // namespace Settings
    } // namespace engine
} // namespace waltz

#endif // ENGINESETTINGS_H
