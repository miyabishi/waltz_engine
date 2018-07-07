#ifndef VERSION_H
#define VERSION_H

#include <QString>

namespace waltz
{
    namespace engine
    {
        namespace dialog
        {

            class Version
            {
            public:
                Version();
                static QString value();
            };

        } // namespace dialog
    } // namespace engine
} // namespace waltz

#endif // VERSION_H
