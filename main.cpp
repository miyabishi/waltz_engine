#include "src/Dialog/InformationDialog/informationdialog.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include "src/Communicator/communicationserver.h"

using namespace waltz::engine::dialog;
using namespace waltz::engine::Communicator;

int main(int argc, char *argv[])
{
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
