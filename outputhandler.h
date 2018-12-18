#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QStackedLayout>
#include <QWidget>

#include "pluniverse.h"

#include "settingsartnet.h"
#include "settingsenttecpro.h"

class OutputHandler : public QObject
{
    Q_OBJECT
public:
    OutputHandler();

    void sendUniverse(PlanktonLighting::PLUniverse *uni);

    QWidget* changeDevice(QString newDev);
    QWidget* getWidget();

private:
    bool stopActiveDevice();

    QString activeOutput = "dummy";
    SettingsArtnet *artnetSettings;
    SettingsEnttecPro *enttecProSettings;
    QWidget *devWid;
};

#endif // OUTPUTHANDLER_H
