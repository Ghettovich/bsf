#include "networkservice.h"
#include <parser/transformpayload.h>
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) :
        QObject(parent) {
    connect(&client, &SocketClient::receivedTcpReply, this, &NetworkService::onTcpReply);
}

void NetworkService::requestPayload(const Arduino &_arduino) {
    arduino = _arduino;
    client.requestFullState(_arduino);
}

void NetworkService::toggleRelay(const Arduino &_arduino, int relayId) {
    arduino = _arduino;
    client.requestToggleRelay(_arduino, relayId);
}

void NetworkService::onReceiveRequestError(QNetworkReply::NetworkError networkError) {
    printf("\nShould update UI with error.");
}

void NetworkService::onTcpReply(const QByteArray &data) {
    TransformPayload transformPayload;

    switch (arduino.getId()) {
        case TransformPayload::ARDUINO_TYPE::BIN_LIFT: {
            int arduinoId = 0;
            Arduino::ARDUINO_STATE newState;
            QVector<IODevice *> ioDeviceList;

            transformPayload.updateArduinoWithPayload(arduinoId, newState, ioDeviceList, data);
            emit sendArduinoWithNewStates(arduino.getId(), newState, ioDeviceList);
            break;
        }
        case TransformPayload::ARDUINO_TYPE::WEIGHT_STATION: {
            // EtherSia only supports single packet request/response and
            // since the headers are sent first with a POST, on the first window and the payload on the second,
            // we receive a reply to 'early' and we fail to update the reserved pointer for the payload
            // So we should never get here untill a single request/response can be made.
            break;
        }
        default:
            printf("Could not determine parsing payload action because arduino id is unknown.\n");
            break;
    }

}

