#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>

class QSystemTrayIcon;
class QAction;
class QMenu;
namespace waltz
{
    namespace engine
    {
        namespace dialog
        {
            class InformationDialog : public QDialog
            {
                Q_OBJECT

            public:
                InformationDialog(QWidget *parent = 0);
                ~InformationDialog();

            private:
                void initializeTrayIcon();

            private slots:
                void showErrorMessage(const QString& aMessage);

            private:
                QSystemTrayIcon& mTrayIcon_;
                QAction&         mQuitAction_;
                QAction&         mShowAction_;
                QMenu&           mTrayIconMenu_;
            };
        }
    }
}

#endif // INFORMATIONDIALOG_H
