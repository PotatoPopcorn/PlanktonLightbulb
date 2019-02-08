#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QHBoxLayout>
#include <QReadLocker>
#include <QVector>
#include <QWidget>

#include "channel.h"
#include "channelupdater.h"
#include "outputhandler.h"

namespace Ui {
class ChannelManager;
}

class ChannelManager : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelManager(QWidget *parent = 0);
    ~ChannelManager();

    bool setChan(int chan, int value);
    bool setChanRAI(int sChan, int eChan, int intv, int value);
    bool setFade(int chan, int value, int time);
    bool setFadeRAI(int sChan, int eChan, int intv, int value, int time);
    void setOutput(OutputHandler *outputHand);

public slots:
    void stopUpdater();

private:
    bool m_outSet = false;

    Ui::ChannelManager *ui;
    QHBoxLayout *m_fadersLayout;

    Channel *m_chans[512];
    ChannelUpdater *m_updater;
};

#endif // CHANNELMANAGER_H
