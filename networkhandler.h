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

public slots:
    void sendMsg(QString msg);

private slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    quint16 m_port = 21000;

    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QHash<QTcpSocket*, QByteArray*> m_buffers;
    QHash<QTcpSocket*, qint32*> m_sizes;

    void dataRecieved(QByteArray data);
    qint32 arrayToInt(QByteArray source);
    QByteArray intToArray(qint32 source);

};

#endif // NETWORKHANDLER_H

//https://stackoverflow.com/questions/20546750/qtcpsocket-reading-and-writing
