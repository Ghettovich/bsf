#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent) : QObject(parent) {
}

void RequestManager::sendGetRequest(QNetworkRequest &_request) {
    reply = qnam.get(_request);

    // CONNECT READY READ
    QObject::connect(reply, &QIODevice::readyRead,
                     this, &RequestManager::onReadyRead);
    // CONNECT ERROR
    connect(reply, &QNetworkReply::errorOccurred,
            this, &RequestManager::onHttpError);
}

void RequestManager::onReadyRead() {
    emit httpCallReady(reply->readAll());
}

void RequestManager::onHttpError(QNetworkReply::NetworkError code) {
    printf("\ngot http error code %s\n", qUtf8Printable(reply->errorString()));
    emit httpError(code);
    reply->deleteLater();
}