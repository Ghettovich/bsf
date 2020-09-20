#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent) : QObject(parent) {
}

void RequestManager::sendGetRequest(QNetworkRequest &_request) {
    reply = qnam.get(_request);

    // CONNECT READY READ
    QObject::connect(reply, &QIODevice::readyRead, this, &RequestManager::onReadyRead);
    // CONNECT ERROR
    connect(reply, &QNetworkReply::errorOccurred,
            this, &RequestManager::onHttpError);
}

void RequestManager::sendRequest(QNetworkRequest& request, QNetworkReply *_reply) {
    reply = _reply;
    sendGetRequest(request);
}

void RequestManager::onReadyRead() {
    emit httpCallReady(reply->readAll());
}

void RequestManager::onHttpError() {
    emit httpError();
}

