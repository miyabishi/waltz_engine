#ifndef PLAYSCORECOMMAND_H
#define PLAYSCORECOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class PlayScoreCommand
                    : public waltz::common::Commands::Command
            {
            public:
                PlayScoreCommand();
            public:
                void exec(
                        const waltz::common::Commands::Parameters &aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PLAYSCORECOMMAND_H
