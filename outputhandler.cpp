#include "outputhandler.h"

OutputHandler::OutputHandler()
{
    devWid = new QWidget();
    QStackedLayout *devLayout = new QStackedLayout();
    devWid->setLayout(devLayout);
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
        QLabel *dummyLabel = new QLabel("This device hasn't been implemented yet");
        devWid->layout()->addWidget(dummyLabel);
    }
    else if(activeOutput == "enttecpro")
    {
        enttecProSettings = new SettingsEnttecPro();
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
        //return enttecProSettings->stopDevice();
    }
    return true;
}
