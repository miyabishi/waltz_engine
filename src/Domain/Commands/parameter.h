#ifndef PARAMETER_H
#define PARAMETER_H

#include <QJsonValue>
#include <QVariant>
#include <QString>

namespace waltz
{
    namespace engine
    {
        namespace Commands
        {
            const QString PARAMETER_KEY_NAME("Name");
            const QString PARAMETER_KEY_VALUE("Value");
            class Parameter
            {
            public:
                Parameter();
                Parameter(const QString& aName,
                          const QVariant& aValue);
                Parameter(const Parameter& aOther);
                Parameter& operator=(const Parameter& aOther);

            public:
                QJsonValue toJsonValue() const;
                QString name() const;
                QString toString() const;
                int toInt() const;
                double toDouble() const;
            private:
                QString  mName_;
                QVariant mValue_;
            };

        } // namespace Commands
    } // namespace engine
} // namespace waltz

#endif // PARAMETER_H
