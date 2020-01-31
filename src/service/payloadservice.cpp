#include "payloadservice.h"
#include <domain/transformpayload.h>
#include <QMetaEnum>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

PayloadService::PayloadService(QObject *parent) : QObject(parent) {
    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::DefaultForPlatform);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagrams()));

    udpSocketWeightStation = new QUdpSocket(this);
    udpSocketWeightStation->bind(6678, QUdpSocket::DefaultForPlatform);
    connect(udpSocketWeightStation, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagramsWeightStation()));
}

void PayloadService::broadcastRecipe(Recipe recipe, const QString& hostAddress, int port) {
    QJsonObject json;
    recipe.writeJson(json);
    QJsonDocument doc(json);
    QByteArray ba = doc.toJson();

    udpSocketWeightStation->writeDatagram(ba, QHostAddress(hostAddress), port);
}

void PayloadService::processDatagram(const QByteArray &data) {
    QVector<IODevice *> ioDeviceList = TransformPayload::transformPayloadToIODeviceList(data);
    emit receivedIODevicesWithNewState(ioDeviceList);
}

void PayloadService::processDatagramWeightStation(const QByteArray &data) {
    // ToDo:implement method
}

void PayloadService::onIncomingDatagrams() {
    QByteArray datagram;
    printf("\nGot incoming udp packets...");

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket->receiveDatagram();
        processDatagram(receiveDatagram.data());
    }
}

void PayloadService::onIncomingDatagramsWeightStation() {
    QByteArray datagram;
    printf("\nGot incoming udp packets from weight station...");

    while (udpSocketWeightStation->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketWeightStation->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocketWeightStation->receiveDatagram();
        processDatagramWeightStation(receiveDatagram.data());
    }
}
