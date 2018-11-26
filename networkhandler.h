#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QSettings>

#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

private slots:
    void sessionOpened();
    void handleConnection();
private:
    QTcpServer *m_tcpServer = nullptr;
    QNetworkSession *m_netSession = nullptr;
    qint16 m_port = 21000;
};

#endif // NETWORKHANDLER_H
