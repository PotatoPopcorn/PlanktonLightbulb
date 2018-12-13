#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QStackedLayout>
#include <QWidget>

#include "settingsenttecpro.h"

class OutputHandler : public QObject
{
    Q_OBJECT
public:
    OutputHandler();

    QWidget* changeDevice(QString newDev);
    QWidget* getWidget();

private:
    bool stopActiveDevice();

    QString activeOutput = "dummy";
    SettingsEnttecPro *enttecProSettings;
    QWidget *devWid;
};

#endif // OUTPUTHANDLER_H
