#include <QCoreApplication>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include "informationdialog.h"
#include "src/Notifier/tasktraynotifier.h"

using namespace waltz::engine::dialog;
using namespace waltz::engine::Notifier;

namespace
{
    const QString INFORMATION_TEXT = "<p><b><big>Waltz Engine<big></b><br />\
<b>Version:</b> 0.0.1 <br />\
<b>GitHub:</b> <a href=\"https://github.com/miyabishi/waltz_engine\">\
https://github.com/miyabishi/waltz_engine</a></p>";
}

InformationDialog::InformationDialog(QWidget *parent)
    : QMessageBox(parent)
    , mTrayIcon_(* (new QSystemTrayIcon(this)))
    , mQuitAction_(*(new QAction(tr("&Quit"), this)))
    , mShowAction_(*(new QAction(tr("&Information"), this)))
    , mTrayIconMenu_(*new QMenu(this))
{
    initializeTrayIcon();
    setText(INFORMATION_TEXT);
}

void InformationDialog::initializeTrayIcon()
{

    mTrayIcon_.setIcon(QIcon(":/vocal.png"));
    mTrayIcon_.show();

    connect(&mQuitAction_, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(&mShowAction_, SIGNAL(triggered(bool)), this, SLOT(show()));
    connect(&TaskTrayNotifier::getInstance(),SIGNAL(notifyErrorSignal(QString)),
            this, SLOT(showErrorMessage(QString)));

    mTrayIconMenu_.addAction(&mShowAction_);
    mTrayIconMenu_.addAction(&mQuitAction_);
    mTrayIcon_.setContextMenu(&mTrayIconMenu_);
}

void InformationDialog::showErrorMessage(const QString &aMessage)
{
    mTrayIcon_.showMessage("Error", aMessage, QSystemTrayIcon::Warning);
}

InformationDialog::~InformationDialog()
{
}
