#include "settingsenttecpro.h"
#include "ui_settingsenttecpro.h"

SettingsEnttecPro::SettingsEnttecPro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsEnttecPro)
{
    ui->setupUi(this);
    utils = new PlanktonLighting::PLEnttecUtilities();
    for (int i = 0; i < utils->countDevices(); i++)
    {
        ui->deviceCombo->addItem(QString::number(i+1));
    }
}

bool SettingsEnttecPro::sendUni(PlanktonLighting::PLUniverse *uni)
{
    if(isRunning)
    {
        return device->sendDMX(uni);
    }
    return false;
}

bool SettingsEnttecPro::stopDevice()
{
    if(isRunning)
    {
        if(device->closeDevice())
        {
            ui->deviceCombo->setEnabled(true);
            ui->universeCombo->setEnabled(true);
            ui->startButton->setEnabled(true);
            ui->stopButton->setEnabled(false);
            isRunning = false;
            qDebug() << "Disonnected";
            delete device;
            return true;
        }
    }
    return false;
}

int SettingsEnttecPro::countDevices()
{
    return utils->countDevices();
}

SettingsEnttecPro::~SettingsEnttecPro()
{
    delete ui;
}

void SettingsEnttecPro::on_startButton_clicked()
{
    device = new PlanktonLighting::PLDeviceEnttecPro();
    QString args;
    args.append(QString::number(ui->deviceCombo->currentText().toInt()-1));
    args.append(" ");
    args.append(ui->universeCombo->currentText());
    if(device->initDevice(args.toStdString()))
    {
        ui->deviceCombo->setEnabled(false);
        ui->universeCombo->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        isRunning = true;
        qDebug() << "Connected";
    }
}

void SettingsEnttecPro::on_stopButton_clicked()
{
    stopDevice();
}
