#ifndef LOADVOICELIBRARYCOMMAND_H
#define LOADVOICELIBRARYCOMMAND_H

#include "command.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class LoadVoiceLibraryCommand : public Command
            {
            public:
                LoadVoiceLibraryCommand();
            public:
                void exec(const Parameters &aParameters);
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // LOADVOICELIBRARYCOMMAND_H
