#include "payloadservice.h"
#include <parser/transformpayload.h>
#include <QMetaEnum>
#include <QHostAddress>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

PayloadService::PayloadService(QObject *parent)
        : QObject(parent), udpSocketManager(this) {

    QObject::connect(&udpSocketManager, &SocketManager::receivedPayload,
                     this, &PayloadService::onParsePayload);

    QObject::connect(&udpSocketManager, &SocketManager::receivedErrorOccured,
                     this, &PayloadService::onReceiveError);

    QObject::connect(&udpSocketManager, &SocketManager::connectedToHost,
                     this, &PayloadService::onFoundHost);
}

void PayloadService::broadcastRecipe(Recipe recipe,int arduinoId, const QString &host, int port) {
    QJsonObject json;
    json["arduinoId"] = arduinoId;
    json["recipeId"] = recipe.getId();
    recipe.writeJson(json);
    QJsonDocument doc(json);
    const QByteArray ba(doc.toJson());
    datagram = QNetworkDatagram(ba, QHostAddress(host), port);

    udpSocketManager.connectoToHost(QHostAddress(host), port);

    //udpSocketManager.broadcastDatagram(datagram);
}

void PayloadService::onReceiveError() {
    printf("Got error\n");
}

void PayloadService::onFoundHost() {
    printf("Found host :)\n");
    if(!datagram.isNull()) {
        udpSocketManager.broadcastDatagram(datagram);
        emit foundArduinoHost();
    }
}

void PayloadService::onParsePayload(const QByteArray& _payload) {
    int arduinoId = 0;
    Arduino::ARDUINO_STATE newState;
    QVector<IODevice *> ioDeviceList;

    TransformPayload::updateArduinoWithPayload(arduinoId, newState, ioDeviceList, _payload);
    emit receivedIODevicesWithNewState(arduinoId, newState, ioDeviceList);
}
