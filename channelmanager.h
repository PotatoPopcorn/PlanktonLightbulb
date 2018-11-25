#ifndef CHANNELMANAGER_H
#define CHANNELMANAGER_H

#include <QHBoxLayout>
#include <QVector>
#include <QWidget>

#include "channel.h"

namespace Ui {
class ChannelManager;
}

class ChannelManager : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelManager(QWidget *parent = 0);
    ~ChannelManager();

private:
    Ui::ChannelManager *ui;
    QHBoxLayout *m_fadersLayout;

    Channel *m_chans[512];
};

#endif // CHANNELMANAGER_H
