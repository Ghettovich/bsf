#include "networkservice.h"
#include <domain/transformpayload.h>
#include <QtNetwork/QNetworkRequest>

NetworkService::NetworkService(QObject *parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
}
void NetworkService::requestPayload() {

}
void NetworkService::requestPayload(QUrl url) {
    QNetworkRequest request;

    if (url.isEmpty()) {
        qDebug("got EMPTY url, falling back to arduino 1 full state payload");
        request.setUrl(QUrl("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/"));
    } else {
        qDebug("got url");
        request.setUrl(QUrl(url));
    }

    reply = networkAccessManager->get(request);
    qInfo() << "sending request...";

    // CLIENT (TCP) INFO
    connect(reply, &QIODevice::readyRead, this, &NetworkService::httpReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &NetworkService::httpError);
    qInfo() << "connected readyread";
}

void NetworkService::httpReadyRead() {
    qInfo() << "Ready for reading, start processing.";
    procesJsonPayload();
}

void NetworkService::httpError() {
    qInfo() << "got http error" << reply->error();
}
void NetworkService::procesJsonPayload() {
    QVector<IODevice *> ioDeviceList = TransformPayload::transformPayloadToIODeviceList(reply->readAll());

    if(ioDeviceList.empty()) {
        qDebug("could not create device list from payload");
    } else {
        emit sendIODeviceListWithNewStates(ioDeviceList);
    }
}
