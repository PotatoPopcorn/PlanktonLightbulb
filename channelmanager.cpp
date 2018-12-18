#include "channelmanager.h"
#include "ui_channelmanager.h"

ChannelManager::ChannelManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelManager)
{
    ui->setupUi(this);

    //Setup Layout
    m_fadersLayout = new QHBoxLayout();
    setLayout(m_fadersLayout);

    //Initialize Channels
    for(int i = 0; i < 512; i++)
    {
        m_chans[i] = new Channel();
        m_chans[i]->setID(i+1);
        m_fadersLayout->addWidget(m_chans[i]);
    }

    m_updater = new ChannelUpdater(m_chans);
    m_updater->start();


}

ChannelManager::~ChannelManager()
{
    delete ui;
}

bool ChannelManager::setChan(int chan, int value)
{
    m_chans[chan-1]->setValue(value);
    return true;
}
