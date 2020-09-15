#include "requestmanager.h"

RequestManager::RequestManager(QObject *parent) : QObject(parent) {
}

void RequestManager::sendGetRequest(QNetworkRequest &_request) {
    reply = qnam.get(_request);

    QObject::connect(reply, &QIODevice::readyRead, this, &RequestManager::readyRead);
}

void RequestManager::sendRequest(const QString& url, QNetworkReply *_reply) {
    reply = _reply;
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    sendGetRequest(request);
}

void RequestManager::readyRead() {
    printf("\nReadyReady lol.");
    emit httpCallReady();
}

