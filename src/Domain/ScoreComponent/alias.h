#ifndef ALIAS_H
#define ALIAS_H

#include <QString>
#include <ialias.h>

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Alias : public waltz::agent::IAlias
            {
            public:
                explicit Alias(const QString& aValue);
                Alias(const Alias& aOther);
                Alias& operator=(const Alias& aOther);

                std::string value() const;

            private:
                QString mValue_;
            };

        } // namespace ScoreComponent
    } // namespace engine
} // namespace watlz

#endif // ALIAS_H
