#include "payloadservice.h"
#include <parser/transformpayload.h>
#include <QMetaEnum>
#include <QHostAddress>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>

PayloadService::PayloadService(QObject *parent)
        : QObject(parent), udpSocketManager(this) {

    QObject::connect(&udpSocketManager, SIGNAL(receivedPayload(const QByteArray&)),
                     this, SLOT(onParsePayload(const QByteArray&)));
}

void PayloadService::broadcastRecipe(Recipe recipe,int arduinoId, const QString &host, int port) {
    QJsonObject json;
    json["arduinoId"] = arduinoId;
    recipe.writeJson(json);
    QJsonDocument doc(json);
    QByteArray ba = doc.toJson();
    QNetworkDatagram datagram(ba, QHostAddress(host), port);

    udpSocketManager.broadcastDatagram(datagram);
}

void PayloadService::onParsePayload(const QByteArray& _payload) {
    int arduinoId = 0;
    Arduino::ARDUINO_STATE newState;
    QVector<IODevice *> ioDeviceList;

    TransformPayload::updateArduinoWithPayload(arduinoId, newState, ioDeviceList, _payload);
    emit receivedIODevicesWithNewState(arduinoId, newState, ioDeviceList);
}
