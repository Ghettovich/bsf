#include "server.h"
#include <QtNetwork/QNetworkDatagram>

Server::Server()
        : QObject() {
    initSocket();
    //connect(&timer, &QTimer::timeout, this, &Server::broadcastDatagram)
}

void Server::setQbyteArrayBroadcastedMsg(const QByteArray &value) {
    qbyteArrayBroadcastedMsg = value;
}

QString Server::getResponseMsg() {
    return QString(qbyteArrayResponseMsg.constData());
}

QString Server::getBroadcastedMsg() {
    return QString(qbyteArrayBroadcastedMsg.constData());
}

int Server::getNrOfMessages() {
    return msgNr;
}

void Server::initSocket() {
    hostAddress = QHostAddress("192.168.178.23");
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(hostAddress, portListenOn);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Server::readPendingDatagrams);
}

void Server::readPendingDatagrams() {
    qInfo() << "Processing...";
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        //QNetworkDatagram datagram = udpSocket->receiveDatagram();
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        this->qbyteArrayResponseMsg = datagram.constData();
    }
}

void Server::broadcastDatagram(quint16 port) {
    this->portBroadcastMsg = port;
    udpSocket->writeDatagram(qbyteArrayBroadcastedMsg, hostAddress, portBroadcastMsg);
    msgNr++;
}

void Server::broadcastDatagram(quint16 port, const char *broadcastDatagramMsg) {
    this->portBroadcastMsg = port;
    this->qbyteArrayBroadcastedMsg = broadcastDatagramMsg;
    udpSocket->writeDatagram(qbyteArrayBroadcastedMsg, hostAddress, portBroadcastMsg);
    msgNr++;
}

bool Server::hasPendingDatagrams() {
    return udpSocket->hasPendingDatagrams();
}
