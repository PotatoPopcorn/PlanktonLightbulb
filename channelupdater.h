#ifndef CHANNELUPDATER_H
#define CHANNELUPDATER_H

#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QTime>

#include "pluniverse.h"

#include "channel.h"

class ChannelUpdater : public QThread
{
public:
    ChannelUpdater(Channel *chans[512]);
    void run();
    void stopRunning();

private:
    bool m_keepAlive = true;
    QMutex m_localLock;

    PlanktonLighting::PLUniverse *m_uni;

    Channel *m_chans[512];
};

#endif // CHANNELUPDATER_H
