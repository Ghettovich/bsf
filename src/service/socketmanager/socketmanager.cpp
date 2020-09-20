#include "socketmanager.h"

SocketManager::SocketManager(QObject *parent) :
        QObject(parent), udpSocket(this) {

    udpSocket.bind(defaultPort, QUdpSocket::DefaultForPlatform);

    QObject::connect(&udpSocket, &QAbstractSocket::errorOccurred,
                     this, &SocketManager::onSocketErrorOccured);

    QObject::connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagrams()));

    QObject::connect(&udpSocket, SIGNAL(hostFound()),
                     this, SLOT(onConnectedWithHost()));
}

void SocketManager::broadcastDatagram(QNetworkDatagram &_datagram) {
    udpSocket.writeDatagram(_datagram);
}

void SocketManager::processDatagram(const QByteArray &payload) {
    emit receivedPayload(payload);
}

void SocketManager::onConnectedWithHost() {
    printf("\nFound host!!");
    emit hostFound();
}

void SocketManager::onSocketErrorOccured() {
    printf("\nudp socket error occured");
    printf("\n%s", qUtf8Printable(udpSocket.errorString()));
}

void SocketManager::onIncomingDatagrams() {
    QByteArray datagram;
    printf("\nGot incoming udp packets...");

    while (udpSocket.hasPendingDatagrams()) {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket.receiveDatagram();
        processDatagram(receiveDatagram.data());
    }
}
