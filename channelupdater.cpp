#include "channelupdater.h"

ChannelUpdater::ChannelUpdater(Channel *chans[512], OutputHandler *outputHand)
{
    m_outHand = outputHand;

    for (int i = 0; i < 512; i++)
    {
        m_chans[i] = chans[i];
    }

    m_uni = new PlanktonLighting::PLUniverse();


}

void ChannelUpdater::run()
{
    m_localLock.lock();
    while(m_keepAlive)
    {
        m_localLock.unlock();
        //qDebug() << "Thread is running: " << QTime::currentTime().msec();
        for (int i = 0; i < 512; i++)
        {
            int val = m_chans[i]->getValue();
            //qDebug() << i << " set to " <<  val;
            m_uni->setChan(i+1, val);
        }
        m_outHand->sendUniverse(m_uni);
        msleep(10);
        m_localLock.lock();
    }
    m_localLock.unlock();

}

void ChannelUpdater::stopRunning()
{
    m_localLock.lock();
    m_keepAlive = false;
    m_localLock.unlock();
}
