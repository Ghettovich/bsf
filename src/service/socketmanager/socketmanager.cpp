#include "socketmanager.h"

SocketManager::SocketManager(QObject *parent) :
        QObject(parent), udpSocket(this) {

    udpSocket.bind(socketManagerPort, QUdpSocket::ShareAddress);

    QObject::connect(&udpSocket, &QUdpSocket::errorOccurred,
                     this, &SocketManager::onSocketErrorOccured);

    QObject::connect(&udpSocket, &QIODevice::readyRead,
            this, &SocketManager::onIncomingDatagrams);

    QObject::connect(&udpSocket, &QUdpSocket::hostFound,
                     this, &SocketManager::onConnectedWithHost);

    QObject::connect(&udpSocket, &QUdpSocket::connected,
                     this, &SocketManager::onConnectionEstablished);
}

int SocketManager::getDefaultPort() const {
    return socketManagerPort;
}

bool SocketManager::isConnectedToHost() {
    return udpSocket.state() == QAbstractSocket::ConnectingState;
}

void SocketManager::broadcastDatagram(QNetworkDatagram &_datagram) {
    udpSocket.writeDatagram(_datagram);
}

void SocketManager::processDatagram(const QByteArray &payload) {
    emit receivedPayload(payload);
}

void SocketManager::onConnectedWithHost() {
    printf("\nFound host blabla !!!!");
    emit connectedToHost();
}

void SocketManager::onSocketErrorOccured() {
    printf("\nudp socket error occured");
    printf("\n%s", qUtf8Printable(udpSocket.errorString()));

    emit receivedErrorOccured();
}

void SocketManager::onConnectionEstablished() {
    printf("\nConnection established!");
    emit connectionEstablished();
}

void SocketManager::onIncomingDatagrams() {
    QByteArray datagram;

    while (udpSocket.hasPendingDatagrams()) {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket.receiveDatagram();
        processDatagram(receiveDatagram.data());
    }
}

void SocketManager::connectoToHost(const QHostAddress& hostAddress, int port) {
    udpSocket.connectToHost(hostAddress, port);
}
