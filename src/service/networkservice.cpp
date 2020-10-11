#include "networkservice.h"
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) :
        QObject(parent) {
    connect(&client, &SocketClient::receivedTcpReply, this, &NetworkService::onTcpReply);
    connect(&tcpServer, &LocalTcpServer::receivedSocketData, this, &NetworkService::onTcpReply);
}

void NetworkService::requestPayload(const Arduino &_arduino) {
    arduino = _arduino;
    client.requestFullState(_arduino);
}

void NetworkService::toggleRelay(const Arduino &_arduino, int relayId) {
    arduino = _arduino;
    client.requestToggleRelay(_arduino, relayId);
}

void NetworkService::setRecipeForWeightstation(const Arduino &_arduino, const Recipe &recipe) {
    arduino = _arduino;
    client.requestSetRecipe(arduino, recipe, SocketClient::EMPTY);
}

void NetworkService::onReceiveRequestError(QNetworkReply::NetworkError networkError) {
    printf("\nShould update UI with error.");
}

void NetworkService::onTcpReply(const QByteArray &data) {
    QJsonDocument jsonDocument(QJsonDocument::fromJson(data));

    if(transformPayload.validateJsonDocument(jsonDocument)) {

        QJsonValue jsonArduinoId (jsonDocument["arduinoId"].toInt());
        int arduinoId = jsonArduinoId.toInt();
        TransformPayload::ARDUINO_TYPE type = transformPayload.identifyArduinoWithId(arduinoId);

        if(type != TransformPayload::ARDUINO_TYPE::UNKOWN) {
            QJsonValue state (jsonDocument["state"]);
            Arduino::ARDUINO_STATE newState = transformPayload.identifyArduinoState(state.toInt());

            onParseSucces(arduinoId, type, newState, jsonDocument);
        }
    } else {
        // ToDo error reporting if service was unable to parse the payload
        printf("\njson doc not valid!");
    }
}

void NetworkService::onParseSucces(int arduinoId,
                                   TransformPayload::ARDUINO_TYPE type,
                                   Arduino::ARDUINO_STATE state,
                                   QJsonDocument& jsonDocument) {
    switch (type) {
        case TransformPayload::ARDUINO_TYPE::BIN_LIFT: {
            QVector<IODevice *> ioDeviceList;
            transformPayload.parseIODeviceItemsInPayload(jsonDocument, ioDeviceList);

            emit sendArduinoWithNewStates(arduinoId, state, ioDeviceList);
            break;
        }
        case TransformPayload::ARDUINO_TYPE::WEIGHT_STATION: {
            IODevice *ioDevice = transformPayload.parseItemWeightStation(jsonDocument);

            if(ioDevice != nullptr) {
                Recipe recipe = transformPayload.addRecipeComponents(jsonDocument);
                ioDevice->setRecipe(recipe);

                emit receivedUpdateForWeightSensor(ioDevice, state);
                printf("\ngot payload for weight station");
            } else {
                printf("\nIODevicie in parsePayload is NULL");
            }

            break;
        }
        default:
            printf("Could not determine parsing payload action because arduino id is unknown.\n");
            break;
    }
}

