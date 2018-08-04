#include "src/Dialog/InformationDialog/informationdialog.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QFileInfo>
#include "src/Communicator/communicationserver.h"
#include "src/Domain/VocalComponent/vocal.h"
#include "src/FileIO/messagefile.h"

#include <QDebug>

using namespace waltz::engine::dialog;
using namespace waltz::engine::Communicator;
using namespace waltz::common::Communicator;
using namespace waltz::common::Commands;

int main(int argc, char *argv[])
{

    if (argc == 2)
    {
        QString filepath(argv[1]);
        waltz::engine::MessageFile messageFile(filepath);
        messageFile.execute();
        return 0;
    }

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(waltzengine);


    if (! QSystemTrayIcon::isSystemTrayAvailable())
    {
        QMessageBox::critical(0, QObject::tr("Systray"),
                               QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    InformationDialog informationDialog;
    informationDialog.hide();

    QObject::connect(
                &CommunicationServer::getInstance(),
                SIGNAL(closed()),
                qApp,
                SLOT(quit()));

    return a.exec();
}
