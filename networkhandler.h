#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QString>

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

signals:
    void commandRecieved(QString cmd);

private slots:
    void sessionOpened();
    void handleConnection();
private:
    QTcpServer *m_tcpServer = nullptr;
    QTcpSocket *m_tcpSocket = nullptr;
    QDataStream *m_inStream;
    QNetworkSession *m_netSession = nullptr;
    quint16 m_port = 21000;
};

#endif // NETWORKHANDLER_H
