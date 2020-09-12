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

void NetworkService::requestPayload(const Arduino &_arduino) {
    arduino = _arduino;
    printf("\nrequestPayload id = %d", arduino.getId());
    requestPayload(arduino.generateQUrl());
}

void NetworkService::requestPayload(const Arduino &_arduino, const QUrl& url) {
    arduino = _arduino;
    printf("\nrequestPayload id = %d\nWith url %s", arduino.getId(), url.toString().toUtf8().constData());
    requestPayload(url);
}

void NetworkService::requestPayload(QNetworkReply &networkReply, const QUrl &url) {
    reply = &networkReply;
    requestPayload(url);
    printf("\nSending request...");
}

void NetworkService::httpReadyRead() {
    printf("\nReady for reading, start processing.");
    procesJsonPayload();
}

void NetworkService::httpError() {
    printf("\ngot http error %u", reply->error());
}

void NetworkService::procesJsonPayload() {
    printf("\nProjectJson id = %d", arduino.getId());
    if(arduino.getId() > 0) {
        int arduinoId= 0;
        Arduino::ARDUINO_STATE newState;
        QVector<IODevice *> ioDeviceList;

        TransformPayload::updateArduinoWithPayload(arduinoId, newState, ioDeviceList, reply->readAll());

        if(arduinoId == arduino.getId()) {
            printf("\nHooray got int arduino id value from payload");
        }

        emit sendArduinoWithNewStates(arduino.getId(), newState, ioDeviceList);

    } else {
        printf("\nNo valid ID set D:");
    }
}
