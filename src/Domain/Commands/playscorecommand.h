#ifndef PLAYSCORECOMMAND_H
#define PLAYSCORECOMMAND_H

#include "command.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class PlayScoreCommand : public Command
            {
            public:
                PlayScoreCommand();
            public:
                void exec(const Parameters &aParameters);
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PLAYSCORECOMMAND_H
