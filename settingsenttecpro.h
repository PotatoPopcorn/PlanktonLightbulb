#ifndef SETTINGSENTTECPRO_H
#define SETTINGSENTTECPRO_H

#include <QDebug>
#include <QWidget>

#include "pldeviceenttecpro.h"
#include "plenttecutilities.h"
#include "pluniverse.h"

namespace Ui {
class SettingsEnttecPro;
}

class SettingsEnttecPro : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsEnttecPro(QWidget *parent = nullptr);
    ~SettingsEnttecPro();

    bool sendUni(PlanktonLighting::PLUniverse *uni);
    bool stopDevice();

public slots:

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    bool isRunning = false;
    Ui::SettingsEnttecPro *ui;

    PlanktonLighting::PLDeviceEnttecPro *device;
    PlanktonLighting::PLEnttecUtilities *utils;
};

#endif // SETTINGSENTTECPRO_H
