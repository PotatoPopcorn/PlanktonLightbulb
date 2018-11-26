#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent)
{
    qDebug() << "Starting Server";
    //Handle network configuration
    //Basically copied from FortuneServer
    QNetworkConfigurationManager netConfigMan;
    if(netConfigMan.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        QSettings netSettings(QSettings::UserScope, QLatin1String("Plankton"), QLatin1String("LightBulb"));
        netSettings.beginGroup(QLatin1String("QtNetwork"));
        const QString networkID = netSettings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        netSettings.endGroup();
        QNetworkConfiguration netConfig = netConfigMan.configurationFromIdentifier(networkID);
        if((netConfig.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered)
        {
            netConfig = netConfigMan.defaultConfiguration();
        }
        m_netSession = new QNetworkSession(netConfig, this);
        connect(m_netSession, &QNetworkSession::opened, this, &NetworkHandler::sessionOpened);
        m_netSession->open();
    }
    else
    {
        sessionOpened();
    }
    connect(m_tcpServer, &QTcpServer::newConnection, this, &NetworkHandler::handleConnection);
}

void NetworkHandler::sessionOpened()
{
    //Handle network configuration
    //Basically copied from FortuneServer
    if(m_netSession){
        QNetworkConfiguration netConfig = m_netSession->configuration();
        QString id;
        if(netConfig.type() == QNetworkConfiguration::UserChoice)
        {
            id = m_netSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        }
        else
        {
            id = netConfig.identifier();
        }
        QSettings netSettings(QSettings::UserScope, QLatin1String("Plankton"), QLatin1String("LightBulb"));
        netSettings.beginGroup(QLatin1String("QtNetwork"));
        netSettings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        netSettings.endGroup();
    }

    m_tcpServer = new QTcpServer(this);
    if(!m_tcpServer->listen(QHostAddress::Any, m_port))
    {
        QMessageBox::critical(nullptr, tr("Plankton LightBulb"), tr("Cannot Start Server: %1").arg(m_tcpServer->errorString()));
    }
}

void NetworkHandler::handleConnection()
{
    //Figureout 2 way communication
}
