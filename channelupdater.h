#ifndef CHANNELUPDATER_H
#define CHANNELUPDATER_H

#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QTime>

#include "pluniverse.h"

#include "channel.h"
#include "outputhandler.h"

class ChannelUpdater : public QThread
{
public:
    ChannelUpdater(Channel *chans[512], OutputHandler *outputHand);
    void run();
    void stopRunning();

private:
    bool m_keepAlive = true;
    QMutex m_localLock;

    PlanktonLighting::PLUniverse *m_uni;

    Channel *m_chans[512];
    OutputHandler *m_outHand;
};

#endif // CHANNELUPDATER_H
