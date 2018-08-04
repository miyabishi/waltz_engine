#include <QFile>
#include "messagefile.h"
#include "src/Communicator/receiveddata.h"

using namespace waltz::engine;

MessageFile::MessageFile(const QString& aFilePath)
    : mFileInfo_(new QFileInfo(aFilePath))
{
}
MessageFile::~MessageFile()
{
    delete mFileInfo_;
}

void MessageFile::execute() const
{
    if (!mFileInfo_->exists() || !mFileInfo_->isFile())
    {
        qWarning("message file is not exists.");
        return;
    }
    QFile file(mFileInfo_->absoluteFilePath());
    file.open(QFile::ReadOnly);
    while(! file.atEnd())
    {
        Communicator::ReceivedData receivedData(file.readLine());
        receivedData.executeCommand();
    }
    file.close();
}

