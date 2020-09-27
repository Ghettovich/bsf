#include "networkservice.h"
#include <parser/transformpayload.h>
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) :
        QObject(parent), requestManager(this) {

    // CONNECT READY READ
    connect(&requestManager, SIGNAL(httpCallReady(const QByteArray &)),
            this, SLOT(onAnswerRequestManager(const QByteArray &)));

    // CONNECT ERROR
    connect(&requestManager, SIGNAL(httpError(QNetworkReply::NetworkError)),
                     this, SLOT(onReceiveRequestError(QNetworkReply::NetworkError)));
}

void NetworkService::requestPayload(const QUrl &url) {
    QNetworkRequest request;

    if (url.isEmpty()) {
        printf("\nGot EMPTY url, falling back to arduino 1 full state payload");
        request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    } else {
        request.setUrl(QUrl(url));
        requestManager.sendGetRequest(request);
    }
}

void NetworkService::requestPayload(const Arduino &_arduino, const QUrl& url) {
    arduino = _arduino;
    requestPayload(url);
}

void NetworkService::sendPostRequest(const Arduino &_arduino, const QUrl &location, const QByteArray &body) {
    arduino = _arduino;
    QNetworkRequest request;
    request.setUrl(location);

    if(location.isEmpty()) {
        printf("\nLocation is empty!??");
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(body.size()));

    requestManager.sendPostRequest(request, body);
}

void NetworkService::procesJsonPayload() {

    switch (arduino.getId()) {
        case TransformPayload::ARDUINO_TYPE::BIN_LIFT: {
            int arduinoId = 0;
            Arduino::ARDUINO_STATE newState;
            QVector<IODevice *> ioDeviceList;

            TransformPayload::updateArduinoWithPayload(arduinoId, newState, ioDeviceList, payload);
            emit sendArduinoWithNewStates(arduino.getId(), newState, ioDeviceList);
            break;
        }
        case TransformPayload::ARDUINO_TYPE::WEIGHT_STATION: {
            QJsonDocument jsonDocument(QJsonDocument::fromJson(payload));

            if(TransformPayload::validateJsonDocument(jsonDocument)) {
                QJsonValue jsonState = jsonDocument["state"];
                Arduino::ARDUINO_STATE state = TransformPayload::identifyArduinoState(jsonState.toInt());
                IODevice *ioDevice = TransformPayload::parseItemWeightStation(jsonDocument);

                emit receivedUpdateForWeightSensor(ioDevice, state);
            }


            break;
        }
        default:
            printf("Could not determine parsing payload action because arduino id is unknown.\n");
            break;
    }

//    if(arduino.getId() > 0) {
//
//
//    } else {
//        // ToDo: Add proper error handling
//        printf("\nNo valid ID set D:");
//    }
}

void NetworkService::onAnswerRequestManager(const QByteArray &_reply) {
    payload = _reply;
    procesJsonPayload();
}

void NetworkService::onReceiveRequestError(QNetworkReply::NetworkError networkError) {
    printf("\nShould update UI with error.");
}
