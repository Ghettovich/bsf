#include "server.h"

#include <QNetworkDatagram>


Server::Server()
    : QObject()
{
    //initSocket();
}

//QUdpSocket* Server::createNewSocket(quint16 port)
//{
//    QUdpSocket *socket = new QUdpSocket(this);
//    socket = new QUdpSocket(this);
//    socket->bind(port, QUdpSocket::ShareAddress);
//    return socket;
//}

void Server::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(PORT, QUdpSocket::ShareAddress);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Server::processPedingDatagrams);
}

void Server::processPedingDatagrams()
{
    const QString *msg;
    QByteArray datagram;
//! [2]
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        msg = new QString(tr("Received datagram: \"%1\"")
                             .arg(datagram.constData()));

        qInfo() << "Message: " << msg;
        //qDebug() << "message:";
    }
//! [2]
}
