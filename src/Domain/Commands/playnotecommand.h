#ifndef PLAYNOTECOMMAND_H
#define PLAYNOTECOMMAND_H

#include "command.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class PlayNoteCommand : public Command
            {
            public:
                PlayNoteCommand();
            public:
                void exec(const Parameters &aParameters);
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PLAYNOTECOMMAND_H
