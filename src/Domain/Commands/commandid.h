#ifndef COMMANDID_H
#define COMMANDID_H

#include <QString>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            class CommandId
            {
            public:
                explicit CommandId(const QString& aValue);
                CommandId(const CommandId& aOther);
                CommandId& operator=(const CommandId& aOther);
                bool operator==(const CommandId& aOther) const;
                bool operator!=(const CommandId& aOther) const;

            public:
                QString value() const;

            private:
                QString mValue_;
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // COMMANDID_H
