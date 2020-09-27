#include "payloadservice.h"
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
    json["componentSize"] = recipe.targetComponentMap.size();
    recipe.writeJson(json);
    QJsonDocument doc(json);
    const QByteArray ba(doc.toJson());
    datagram = QNetworkDatagram(ba, QHostAddress(host), port);

    udpSocketManager.connectoToHost(QHostAddress(host), port);
}

void PayloadService::onReceiveError() {
    // ToDo: update ui properly with error messages
    emit receivedError();
}

void PayloadService::onFoundHost() {
    if(!datagram.isNull()) {
        udpSocketManager.broadcastDatagram(datagram);
        emit foundArduinoHost();
    }
}

void PayloadService::onParsePayload(const QByteArray& _payload) {
    QJsonDocument jsonDocument(QJsonDocument::fromJson(_payload));

    if(TransformPayload::validateJsonDocument(jsonDocument)) {

        QJsonValue jsonArduinoId (jsonDocument["arduinoId"].toInt());
        int arduinoId = jsonArduinoId.toInt();
        TransformPayload::ARDUINO_TYPE type = TransformPayload::identifyArduinoWithId(arduinoId);
        //TransformPayload::identifyArduino(arduinoId, type);

        if(type != TransformPayload::ARDUINO_TYPE::UNKOWN) {
            QJsonValue state (jsonDocument["state"]);
            Arduino::ARDUINO_STATE newState = TransformPayload::identifyArduinoState(state.toInt());
            //TransformPayload::identifyArduinoState(state.toInt(), newState);

            parsePayload(arduinoId, type, newState, jsonDocument);
        }
    } else {
        // ToDo error reporting if service was unable to parse the payload
    }
}

void PayloadService::parsePayload(int arduinoId,
                                  TransformPayload::ARDUINO_TYPE type,
                                  Arduino::ARDUINO_STATE state,
                                  QJsonDocument& jsonDocument) {
    switch (type) {
        case TransformPayload::ARDUINO_TYPE::BIN_LIFT: {
            QVector<IODevice *> ioDeviceList;
            TransformPayload::parseIODeviceItemsInPayload(jsonDocument, ioDeviceList);

            emit receivedIODevicesWithNewState(arduinoId, state, ioDeviceList);
            break;
        }
        case TransformPayload::ARDUINO_TYPE::WEIGHT_STATION: {
            IODevice *ioDevice = TransformPayload::parseItemWeightStation(jsonDocument);

            printf("\ngot payload for weight station");

            emit receivedUpdateForWeightSensor(ioDevice, state);

            break;
        }
        default:
            printf("Could not determine parsing payload action because arduino id is unknown.\n");
            break;
    }
}


