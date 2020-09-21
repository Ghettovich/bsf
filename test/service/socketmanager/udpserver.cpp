#include "udpserver.h"
#include <QtNetwork/QNetworkDatagram>

UdpServer::UdpServer(QObject *parent) :
        QObject(parent) {
    udpServerSocket = new QUdpSocket(parent);
    udpServerSocket->bind(QHostAddress::LocalHost, port, QUdpSocket::DefaultForPlatform);

    QObject::connect(udpServerSocket, SIGNAL(readyRead()),
                     this, SLOT(onIncomingDatagrams()));
}

int UdpServer::getPort() const {
    return port;
}

void UdpServer::broadcastDatagram(QNetworkDatagram &_datagram) {
    udpServerSocket->writeDatagram(_datagram);
}

void UdpServer::onIncomingDatagrams() {
    QByteArray datagram;

    while (udpServerSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpServerSocket->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpServerSocket->receiveDatagram();
        emit receivedPayload(receiveDatagram.data());
    }
}
