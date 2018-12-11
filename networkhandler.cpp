#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent)
{
    qDebug() << "Starting Server";
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &NetworkHandler::newConnection);
    qDebug() << "Listening: " << m_server->listen(QHostAddress::Any, m_port);
}

void NetworkHandler::newConnection()
{
    while(m_server->hasPendingConnections())
    {
        QTcpSocket *socket = m_server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &NetworkHandler::readyRead);
        connect(socket, &QTcpSocket::disconnected, this, &NetworkHandler::disconnected);
        QByteArray *buffer = new QByteArray();
        qint32 *s = new qint32(0);
        m_buffers.insert(socket, buffer);
        m_sizes.insert(socket, s);
    }
}

void NetworkHandler::disconnected()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = m_buffers.value(socket);
    qint32 *s = m_sizes.value(socket);
    socket->deleteLater();
    delete buffer;
    delete s;
}

void NetworkHandler::readyRead()
{
    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    QByteArray *buffer = m_buffers.value(socket);
    qint32 *s = m_sizes.value(socket);
    qint32 size = *s;
    while(socket->bytesAvailable() > 0)
    {
        buffer->append(socket->readAll());
        while((size == 0 && buffer->size() >=4) || (size > 0 && buffer->size() >= size))
        {
            if (size == 0 && buffer->size() >=4)
            {
                size = arrayToInt(buffer->mid(0, 4));
                *s = size;
                buffer->remove(0, 4);
            }
            if (size > 0 && buffer->size() >= size)
            {
                QByteArray data = buffer->mid(0, size);
                buffer->remove(0,size);
                size=0;
                *s = size;
                dataRecieved(data);
            }
        }
    }
}

void NetworkHandler::dataRecieved(QByteArray data)
{
    QString s_data = QString::fromLatin1(data.data());
    qDebug() << "Data Recieved: " << s_data;
}

qint32 NetworkHandler::arrayToInt(QByteArray source)
{
    qint32 temp;
    QDataStream data(&source, QIODevice::ReadWrite);
    data >> temp;
    return temp;
}
