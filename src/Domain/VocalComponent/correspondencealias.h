#ifndef CORRESPONDENCEALIAS_H
#define CORRESPONDENCEALIAS_H

#include <QSharedPointer>
#include <waltz_common/parameters.h>

namespace waltz
{
    namespace engine
    {
        namespace VocalComponent
        {
            class CorrespondenceAlias
            {
            public:
                explicit CorrespondenceAlias(const QString& aValue);
                waltz::common::Commands::Parameters toParameters() const;

            private:
                QString mValue_;
            };
            typedef QSharedPointer<CorrespondenceAlias> CorrespondenceAliasPointer;
        } // namespace VocalComponent
    } // namespace engine
} // namespace waltz

#endif // CORRESPONDENCEALIAS_H
