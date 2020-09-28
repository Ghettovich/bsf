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

void NetworkService::procesJsonPayload() {
    TransformPayload transformPayload;

    switch (arduino.getId()) {
        case TransformPayload::ARDUINO_TYPE::BIN_LIFT: {
            int arduinoId = 0;
            Arduino::ARDUINO_STATE newState;
            QVector<IODevice *> ioDeviceList;

            transformPayload.updateArduinoWithPayload(arduinoId, newState, ioDeviceList, payload);
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

void NetworkService::onAnswerRequestManager(const QByteArray &_reply) {
    payload = _reply;
    procesJsonPayload();
}

void NetworkService::onReceiveRequestError(QNetworkReply::NetworkError networkError) {
    printf("\nShould update UI with error.");
}