#ifndef CORRESPONDENCEALIASLIST_H
#define CORRESPONDENCEALIASLIST_H

#include <QSharedPointer>
#include <QList>
#include <vector>
#include <string>
#include <waltz_common/parameter.h>

#include "correspondencealias.h"

namespace waltz
{
    namespace engine
    {
        namespace VocalComponent
        {
            class CorrespondenceAliasList
            {
            public:
                CorrespondenceAliasList(const std::vector<std::string> aAliasVector);

            public:
                waltz::common::Commands::Parameter toParameter() const;

            private:
                QList<CorrespondenceAliasPointer> mCorrespondenceAliasList_;

            };
            typedef QSharedPointer<CorrespondenceAliasList> CorrespondenceAliasListPointer;

        } // namespace VocalComponent
    } // namespace engine
} // namespace waltz

#endif // CORRESPONDENCEALIASLIST_H
