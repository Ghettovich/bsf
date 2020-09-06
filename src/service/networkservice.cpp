#include "networkservice.h"
#include <domain/transformpayload.h>
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
}

void NetworkService::requestPayload(const QUrl &url) {
    QNetworkRequest request;

    if (url.isEmpty()) {
        printf("\nGot EMPTY url, falling back to arduino 1 full state payload");
        request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    } else {
        printf("\nGot url");
        request.setUrl(QUrl(url));
    }

    reply = networkAccessManager->get(request);
    printf("\nSending request...");

    // CLIENT (TCP) INFO
    connect(reply, &QIODevice::readyRead, this, &NetworkService::httpReadyRead);
    connect(reply, &QNetworkReply::errorOccurred,
            this, &NetworkService::httpError);
    printf("\nConnected readyread");
}

void NetworkService::requestPayload(Arduino *_arduino) {
    if (_arduino != nullptr) {
        arduino = _arduino;
        requestPayload(arduino->generateQUrl());
    } else {
        printf("got null");
    }
}

void NetworkService::httpReadyRead() {
    printf("\nReady for reading, start processing.");
    procesJsonPayload();
}

void NetworkService::httpError() {
    printf("\ngot http error %u", reply->error());
}

void NetworkService::procesJsonPayload() {
    if(arduino != nullptr) {
        QVector<IODevice *> ioDeviceList;

        TransformPayload::updateArduinoWithPayload(arduino, ioDeviceList, reply->readAll());
        int arduinoId = arduino->getId();
        Arduino::ARDUINO_STATE state = arduino->getArduinoState();

        emit sendArduinoWithNewStates(arduinoId, state, ioDeviceList);
        delete arduino;

    } else {
        QVector<IODevice *> ioDeviceList = TransformPayload::transformPayloadToIODeviceList(reply->readAll());

        if (ioDeviceList.empty()) {
            printf("\nCould not create device list from payload");
        } else {
            emit sendIODeviceListWithNewStates(ioDeviceList);
        }
    }
}
