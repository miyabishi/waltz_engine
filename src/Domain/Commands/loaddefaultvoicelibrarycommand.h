#ifndef LOADDEFAULTVOICELIBRARYCOMMAND_H
#define LOADDEFAULTVOICELIBRARYCOMMAND_H

#include <waltz_common/command.h>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class LoadDefaultVoiceLibraryCommand
                    : public waltz::common::Commands::Command
            {
            public:
                LoadDefaultVoiceLibraryCommand();
                void exec(
                   const waltz::common::Commands::Parameters& aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // LOADDEFAULTVOICELIBRARYCOMMAND_H
