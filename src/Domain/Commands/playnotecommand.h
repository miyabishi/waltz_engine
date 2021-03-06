#ifndef PLAYNOTECOMMAND_H
#define PLAYNOTECOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class PlayNoteCommand
                    : public waltz::common::Commands::Command
            {
            public:
                PlayNoteCommand();
            public:
                void exec(
                        const waltz::common::Commands::Parameters &aParameters);
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PLAYNOTECOMMAND_H
