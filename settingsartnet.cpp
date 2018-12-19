#include "settingsartnet.h"
#include "ui_settingsartnet.h"

SettingsArtnet::SettingsArtnet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsArtnet)
{
    ui->setupUi(this);
}

SettingsArtnet::~SettingsArtnet()
{
    delete ui;
}

bool SettingsArtnet::sendUni(PlanktonLighting::PLUniverse *uni)
{
    if(isRunning)
    {
        return device->sendDMX(uni);
    }
    return false;
}

bool SettingsArtnet::stopDevice()
{
    if(isRunning)
    {
        if(device->closeDevice())
        {
            ui->addressEdit->setEnabled(true);
            ui->portEdit->setEnabled(true);
            ui->physicalEdit->setEnabled(true);
            ui->subNetEdit->setEnabled(true);
            ui->netEdit->setEnabled(true);
            ui->sequenceBox->setEnabled(true);
            ui->startButton->setEnabled(true);
            ui->stopButton->setEnabled(false);
            isRunning = false;
            return true;
        }
    }
    return false;
}

void SettingsArtnet::on_startButton_clicked()
{
    device = new PlanktonLighting::PLDeviceArtnet();
    QString args;
    args.append(ui->addressEdit->text());
    args.append(" ");
    args.append(ui->portEdit->text());
    args.append(" ");
    args.append(ui->physicalEdit->text());
    args.append(" ");
    args.append(ui->subNetEdit->text());
    args.append(" ");
    args.append(ui->netEdit->text());
    args.append(" ");
    if(ui->sequenceBox->currentText() == "On")
    {
        args.append("1");
    }
    else
    {
        args.append("0");
    }
    if(device->initDevice(args.toStdString()))
    {
        ui->addressEdit->setEnabled(false);
        ui->portEdit->setEnabled(false);
        ui->physicalEdit->setEnabled(false);
        ui->subNetEdit->setEnabled(false);
        ui->netEdit->setEnabled(false);
        ui->sequenceBox->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->stopButton->setEnabled(true);
        isRunning = true;
        qDebug() << "Running";
    }
}

void SettingsArtnet::on_stopButton_clicked()
{
    stopDevice();
}
