#include "outputhandler.h"

OutputHandler::OutputHandler()
{
    devWid = new QWidget();
    QStackedLayout *devLayout = new QStackedLayout();
    devWid->setLayout(devLayout);

    artnetSettings = new SettingsArtnet();
    enttecProSettings = new SettingsEnttecPro();
}

void OutputHandler::sendUniverse(PlanktonLighting::PLUniverse *uni)
{
    if(activeOutput == "enttecpro")
    {
        enttecProSettings->sendUni(uni);
    }
    else if (activeOutput == "artnet")
    {
        artnetSettings->sendUni(uni);
    }
}

bool OutputHandler::deviceExists(QString device)
{
    if(device == "dummy" || device == "artnet")
    {
        return true;
    }
    else if(device == "enttecpro")
    {
        return enttecProSettings->countDevices() != 0;
    }
    return false;
}

QWidget* OutputHandler::changeDevice(QString newDev)
{
    while (QLayoutItem *item = devWid->layout()->takeAt(0)) {
        devWid->layout()->removeItem(item);
    }
    qDebug() << "NewDev " << newDev;
    stopActiveDevice();
    activeOutput = newDev;
    if(activeOutput == "dummy"){
        QLabel *dummyLabel = new QLabel("This device has no settings");
        devWid->layout()->addWidget(dummyLabel);
    }
    else if(activeOutput == "artnet"){
        devWid->layout()->addWidget(artnetSettings);
    }
    else if(activeOutput == "enttecpro")
    {
        devWid->layout()->addWidget(enttecProSettings);
    }
    return devWid;
}

QWidget* OutputHandler::getWidget(){
    return devWid;
}

bool OutputHandler::stopActiveDevice()
{
    if(activeOutput == "enttecpro")
    {
        return enttecProSettings->stopDevice();
    }
    else if (activeOutput == "artnet")
    {
        return artnetSettings->stopDevice();
    }
    return true;
}
