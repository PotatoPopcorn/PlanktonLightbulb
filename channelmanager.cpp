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

bool ChannelManager::setChanRAI(int sChan, int eChan, int intv, int value)
{
    for(int i = sChan; i <= eChan; i += intv){
        setChan(i, value);
    }
    return true;
}

bool ChannelManager::setFade(int chan, int value, int time)
{
    m_chans[chan-1]->setFade(value, time);
    return true;
}

bool ChannelManager::setFadeRAI(int sChan, int eChan, int intv, int value, int time)
{
    qDebug() <<"RAI: " << sChan << eChan << intv << value << time;
    for(int i = sChan; i <= eChan; i += intv){
        setFade(i, value, time);
    }
    return true;
}

void ChannelManager::setOutput(OutputHandler *outputHand)
{
    m_updater = new ChannelUpdater(m_chans, outputHand);
    m_updater->start();
}

void ChannelManager::stopUpdater()
{
    m_updater->stopRunning();
}
