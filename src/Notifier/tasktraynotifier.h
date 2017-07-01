#ifndef TASKTRAYNOTIFIER_H
#define TASKTRAYNOTIFIER_H

#include <QObject>

namespace waltz
{
    namespace engine
    {
        namespace Notifier
        {

            class TaskTrayNotifier : public QObject
            {
                Q_OBJECT
            public:
                static TaskTrayNotifier& getInstance();
                void notifyError(const QString& aMessage);

            signals:
                void notifyErrorSignal(const QString& aMessage);

            public slots:
            private:
                static TaskTrayNotifier* mInstance_;

            private:
                explicit TaskTrayNotifier(QObject *aParent = 0);
            };

        } // namespace Notifier
    } // namespace engine
} // namespace waltz

#endif // TASKTRAYNOTIFIER_H
