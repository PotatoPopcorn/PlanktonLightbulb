#ifndef SETTINGSARTNET_H
#define SETTINGSARTNET_H

#include <QDebug>
#include <QWidget>

#include "pldeviceartnet.h"
#include "pluniverse.h"

namespace Ui {
class SettingsArtnet;
}

class SettingsArtnet : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsArtnet(QWidget *parent = nullptr);
    ~SettingsArtnet();

    bool sendUni(PlanktonLighting::PLUniverse *uni);
    bool stopDevice();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    bool isRunning = false;
    Ui::SettingsArtnet *ui;

    PlanktonLighting::PLDeviceArtnet *device;
};

#endif // SETTINGSARTNET_H
