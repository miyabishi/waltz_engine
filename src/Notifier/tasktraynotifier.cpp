#include "tasktraynotifier.h"

using namespace waltz::engine::Notifier;

TaskTrayNotifier* TaskTrayNotifier::mInstance_ = 0;

TaskTrayNotifier& TaskTrayNotifier::getInstance()
{
    if (mInstance_ == 0)
    {
        static TaskTrayNotifier instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

void TaskTrayNotifier::notifyError(const QString& aMessage)
{
    emit notifyErrorSignal(aMessage);
}

TaskTrayNotifier::TaskTrayNotifier(QObject *parent) : QObject(parent)
{

}
