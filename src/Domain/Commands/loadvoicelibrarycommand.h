#ifndef LOADVOICELIBRARYCOMMAND_H
#define LOADVOICELIBRARYCOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class LoadVoiceLibraryCommand
                    : public waltz::common::Commands::Command
            {
            public:
                LoadVoiceLibraryCommand();
            public:
                void exec(
                   const waltz::common::Commands::Parameters& aParameters);
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // LOADVOICELIBRARYCOMMAND_H
