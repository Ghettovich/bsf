#include "networkservice.h"
#include <parser/transformpayload.h>
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) :
        QObject(parent), requestManager(this) {

    // CONNECT READY READ
    connect(&requestManager, SIGNAL(httpCallReady(const QByteArray &)),
            this, SLOT(onAnswerRequestManager(const QByteArray &)));

    // CONNECT ERROR
    connect(&requestManager, SIGNAL(httpError()),
                     this, SLOT(onReceiveRequestError()));
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

void NetworkService::requestPayload(const Arduino &_arduino) {
    arduino = _arduino;
    requestPayload(arduino.generateQUrl());
}

void NetworkService::requestPayload(const Arduino &_arduino, const QUrl& url) {
    arduino = _arduino;
    requestPayload(url);
}

void NetworkService::procesJsonPayload() {
    if(arduino.getId() > 0) {
        int arduinoId= 0;
        Arduino::ARDUINO_STATE newState;
        QVector<IODevice *> ioDeviceList;

        TransformPayload::updateArduinoWithPayload(arduinoId, newState, ioDeviceList, payload);
        emit sendArduinoWithNewStates(arduino.getId(), newState, ioDeviceList);

    } else {
        // ToDo: Add proper error handling
        printf("\nNo valid ID set D:");
    }
}

void NetworkService::onAnswerRequestManager(const QByteArray &_reply) {
    payload = _reply;
    procesJsonPayload();
}

void NetworkService::onReceiveRequestError() {
    printf("\ngot http error %u", reply->error());
}
