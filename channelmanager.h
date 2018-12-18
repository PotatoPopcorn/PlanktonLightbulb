#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QHBoxLayout>
#include <QReadLocker>
#include <QVector>
#include <QWidget>

#include "channel.h"
#include "channelupdater.h"

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

private:
    Ui::ChannelManager *ui;
    QHBoxLayout *m_fadersLayout;

    Channel *m_chans[512];
    ChannelUpdater *m_updater;
};

#endif // CHANNELMANAGER_H
