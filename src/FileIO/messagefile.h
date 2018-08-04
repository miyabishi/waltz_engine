#ifndef MESSAGEFILE_H
#define MESSAGEFILE_H

#include <QString>
#include <QFileInfo>

namespace waltz
{
    namespace engine
    {
        class MessageFile
        {
        public:
            explicit MessageFile(const QString& aFilePath);
            ~MessageFile();
            void execute() const;

        private:
            QFileInfo* mFileInfo_;
        };
    } // namespace engine
} // namespace waltz

#endif // MESSAGEFILE_H
