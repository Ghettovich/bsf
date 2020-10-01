#include "socketmanager.h"

SocketManager::SocketManager(QObject *parent) :
        QObject(parent), udpSocket(this) {

    udpSocket.bind(socketManagerPort, QUdpSocket::ShareAddress);

    QObject::connect(&udpSocket, &QUdpSocket::errorOccurred,
                     this, &SocketManager::onSocketErrorOccured);

    QObject::connect(&udpSocket, &QIODevice::readyRead,
            this, &SocketManager::onIncomingDatagrams);
}

void SocketManager::broadcastDatagram(const QNetworkDatagram &_datagram) {
    udpSocket.writeDatagram(_datagram);
}

int SocketManager::getDefaultPort() const {
    return socketManagerPort;
}

QString SocketManager::getSocketErrorMessage() {
    return udpSocket.errorString();
}

void SocketManager::processDatagram(const QByteArray &payload) {
    emit receivedPayload(payload);
}

void SocketManager::onIncomingDatagrams() {
    QByteArray datagram;

    while (udpSocket.hasPendingDatagrams()) {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket.receiveDatagram();
        processDatagram(receiveDatagram.data());
    }
}

void SocketManager::onSocketErrorOccured(QAbstractSocket::SocketError socketError) {
    if(socketError == QAbstractSocket::HostNotFoundError) {
        emit arduinoNotFound();
    }
    printf("\n%s \n", qUtf8Printable(getSocketErrorMessage()));

    emit receivedErrorOccured();
}
