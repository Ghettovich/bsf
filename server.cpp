#include "server.h"
#include <QtNetwork/QNetworkDatagram>

Server::Server()
    : QObject()
{
    initSocket();
    //connect(&timer, &QTimer::timeout, this, &Server::broadcastDatagram)
}

void Server::setQbyteArrayBroadcastedMsg(const QByteArray &value)
{
    qbyteArrayBroadcastedMsg = value;
}

QString Server::getResponseMsg()
{
    return QString(qbyteArrayResponseMsg.constData());
}

QString Server::getBroadcastedMsg()
{
    return QString(qbyteArrayBroadcastedMsg.constData());
}

int Server::getNrOfMessages()
{
    return msgNr;
}

void Server::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(portListenOn, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
}

void Server::processPendingDatagrams()
{
    //QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        qbyteArrayResponseMsg.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(qbyteArrayResponseMsg.data(), qbyteArrayResponseMsg.size());

        qInfo() << "Message: " << QString(qbyteArrayResponseMsg.constData());
        //qDebug() << "message:";
    }
}

void Server::broadcastDatagram(quint16 port)
{
    this->portBroadcastMsg = port;
    udpSocket->writeDatagram(qbyteArrayBroadcastedMsg, QHostAddress::Broadcast, port);
    msgNr++;
}

void Server::broadcastDatagram(quint16 port, const char *broadcastDatagramMsg)
{
    this->portBroadcastMsg = port;
    this->qbyteArrayBroadcastedMsg = broadcastDatagramMsg;

    //Unnecessary
    //QByteArray datagram = broadcastDatagramMsg;

    udpSocket->writeDatagram(qbyteArrayBroadcastedMsg, QHostAddress::Broadcast, port);
    msgNr++;
}
