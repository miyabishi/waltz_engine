#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>


namespace waltz
{
    namespace engine
    {
        namespace Commands
        {

            class ExitCommand : public waltz::common::Commands::Command
            {
            public:
                ExitCommand();

            public:
                void exec(
                   const waltz::common::Commands::Parameters& aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // EXITCOMMAND_H
