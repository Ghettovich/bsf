#include "udpserver.h"
#include <QtNetwork/QNetworkDatagram>

UdpServer::UdpServer(QObject *parent) :
        QObject(parent), udpServerSocket(this) {
    //udpServerSocket = new QUdpSocket(parent);

    udpServerSocket.bind(port, QUdpSocket::ShareAddress);


    QObject::connect(&udpServerSocket, &QIODevice::readyRead,
                     this, &UdpServer::onIncomingDatagrams);

    QObject::connect(&udpServerSocket, &QUdpSocket::errorOccurred,
                     this, &UdpServer::onSocketErrorOccured);

    QObject::connect(&udpServerSocket, &QUdpSocket::hostFound,
                     this, &UdpServer::onConnectedWithHost);

    QObject::connect(&udpServerSocket, &QUdpSocket::connected,
                     this, &UdpServer::onConnectionEstablished);
}

int UdpServer::getPort() const {
    return port;
}

void UdpServer::broadcastDatagram(QNetworkDatagram &_datagram) {
    udpServerSocket.writeDatagram(_datagram);
}

void UdpServer::onIncomingDatagrams() {
    QByteArray datagram;

    while (udpServerSocket.hasPendingDatagrams()) {
        datagram.resize(int(udpServerSocket.pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpServerSocket.receiveDatagram();
        emit receivedPayload(receiveDatagram.data());
    }
}

void UdpServer::onSocketErrorOccured() {
    printf("\nudp socket error occured");
    printf("\n%s", qUtf8Printable(udpServerSocket.errorString()));

    emit receivedErrorOccured();
}

void UdpServer::onConnectedWithHost() {
    printf("\nFound host blabla !!!!");
    emit connectedToHost();
}

void UdpServer::onConnectionEstablished() {
    printf("\nConnection established!");
    emit connectionEstablished();
}
