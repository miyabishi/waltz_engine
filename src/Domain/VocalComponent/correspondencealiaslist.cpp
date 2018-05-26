#include "correspondencealiaslist.h"
#include <waltz_common/parameterslist.h>

using namespace waltz::engine::VocalComponent;
using namespace waltz::common::Commands;

namespace
{
    const QString PARAMETER_NAME_CORRESPONDENCE_ALIAS_LIST("CorrespondenceAliasList");
}

CorrespondenceAliasList::CorrespondenceAliasList(const std::vector<std::string> aAliasVector)
    :mCorrespondenceAliasList_()
{
    for (std::vector<std::string>::const_iterator iterator = aAliasVector.cbegin();
         iterator != aAliasVector.cend();
         ++iterator)
    {
        mCorrespondenceAliasList_.append(
                    CorrespondenceAliasPointer(
                        new CorrespondenceAlias(QString::fromStdString(*iterator))));
    }
}

Parameter CorrespondenceAliasList::toParameter() const
{
    ParametersList parameterList;

    foreach(const CorrespondenceAliasPointer correspondenceAlias, mCorrespondenceAliasList_)
    {
        parameterList.append(correspondenceAlias->toParameters());
    }
    return Parameter(PARAMETER_NAME_CORRESPONDENCE_ALIAS_LIST,
                     parameterList.toJsonArray());
}
