#include "payloadservice.h"
#include <domain/transformpayload.h>
#include <QMetaEnum>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

PayloadService::PayloadService(QObject *parent) : QObject(parent) {

    // HOST (UDP) INFO
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6677, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(onIncomingDatagrams()));

    udpSocketWeightStation = new QUdpSocket(this);
    udpSocketWeightStation->bind(6678, QUdpSocket::ShareAddress);
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
//    qInfo() << "processing datagrams weight station";
//    ArduinoDTO arduinoDto = TransformPayload::transformJSONPayloadToArduinoDto(data);
//
//    qInfo() << "state reply =" << QString::number(arduinoDto.stateReply);
//    qInfo() << "arduino id =" << QString::number(arduinoDto.arduinoId);
//
//    if (arduino != nullptr && arduinoDto.arduinoId == arduino->id) {
//        // weight station parsed json succesfully
//        if (arduinoDto.stateReply == PARSED_RECIPE_SUCCESSFULL) {
//            emit onReceiveWeightStationReply(data);
//        } else {
//            qInfo() << "state reply unknown";
//        }
//
//        arduino = nullptr;
//    } else {
//        qInfo() << "received UDP packets from WEIGHT STATION";
//        if (arduinoDto.stateReply == UPDATE_WEIGHT_SENSOR) {
//            emit onReceiveWeightSensorData(arduinoDto.deviceId, arduinoDto.componentId, arduinoDto.weight);
//        } else if (arduinoDto.stateReply == WEIGHT_STATION_IDLE) {
//            qInfo() << "idle reply...";
//        } else {
//            qInfo() << "state reply unknown";
//        }
//    }
}

void PayloadService::onIncomingDatagrams() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets...";

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocket->receiveDatagram();
        processDatagram(receiveDatagram.data());
    }
}

void PayloadService::onIncomingDatagramsWeightStation() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets from weight station...";

    while (udpSocketWeightStation->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketWeightStation->pendingDatagramSize()));
        QNetworkDatagram receiveDatagram = udpSocketWeightStation->receiveDatagram();
        processDatagramWeightStation(receiveDatagram.data());
    }
}
