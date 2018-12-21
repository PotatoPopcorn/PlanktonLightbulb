#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QString>

#include "pldeviceenttecpro.h"
#include "pluniverse.h"

#include "channelmanager.h"
#include "networkhandler.h"
#include "settingspanel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent* event);

public slots:
    void recieveCommand(QString cmd);

private:
    Ui::MainWindow *ui;
    QStackedLayout *faderLayout;

    ChannelManager *chans;
    NetworkHandler *networkHand;
    SettingsPanel *settingsTab;
};

#endif // MAINWINDOW_H
