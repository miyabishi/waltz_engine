#ifndef SAVEWAVCOMMAND_H
#define SAVEWAVCOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class SaveWavCommand
                    : public waltz::common::Commands::Command
            {
            public:
                SaveWavCommand();
            public:
                void exec(
                   const waltz::common::Commands::Parameters& aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // SAVEWAVCOMMAND_H
