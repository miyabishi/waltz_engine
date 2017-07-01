#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QMap>
#include <QJsonArray>
#include "parameter.h"

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {

            class Parameters
            {
            public:
                Parameters();
                Parameters(const Parameters& aOther);
                Parameters& operator=(const Parameters& aOther);

            public:
                void append(const Parameter& aParameter);
                Parameter find(const QString& aParameterName) const;
                QJsonArray toJsonArray() const;

            private:
                QMap<QString, Parameter> mParameters_;
            };
        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PARAMETERS_H
