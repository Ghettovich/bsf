#include "socketclient.h"
#include <recipe.h>
#include <QtNetwork/QHostAddress>
#include <QtCore/QDataStream>

SocketClient::SocketClient(QObject *parent) : QObject(parent) {
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &SocketClient::onErrorOccured);
    connect(tcpSocket, &QTcpSocket::stateChanged, this, &SocketClient::onSocketStateChange);
    connect(tcpSocket, &QIODevice::readyRead, this, &SocketClient::onReadyRead);
}

void SocketClient::requestFullState(const Arduino &_arduino, ReplyWithCode replyCode) {
    QJsonObject jsonPayloadObject;
    jsonPayloadObject["replyCode"] = replyCode;

    doc = QJsonDocument(jsonPayloadObject);
    QHostAddress host(_arduino.getIpAddress());

    if(tcpSocket->state() != QAbstractSocket::ConnectingState) {
        tcpSocket->connectToHost(host, _arduino.getPort());
    }
}

void SocketClient::requestToggleRelay(const Arduino &_arduino, int relayId, ReplyWithCode replyCode) {
    QJsonObject jsonPayloadObject;
    jsonPayloadObject["replyCode"] = replyCode;
    jsonPayloadObject["toggleRelayId"] = relayId;

    doc = QJsonDocument(jsonPayloadObject);
    QHostAddress host(_arduino.getIpAddress());

    if(tcpSocket->state() != QAbstractSocket::ConnectingState) {
        tcpSocket->connectToHost(host, _arduino.getPort());
    }
}

void
SocketClient::requestSetRecipe(const Arduino &_arduino, Recipe recipe, SocketClient::ReplyWithCode replyCode) {
    QJsonObject jsonPayloadObject;
    jsonPayloadObject["replyCode"] = replyCode;
    jsonPayloadObject["arduinoId"] = _arduino.getId();
    jsonPayloadObject["recipeId"] = recipe.getId();
    jsonPayloadObject["componentSize"] = recipe.targetComponentMap.size();
    recipe.writeJson(jsonPayloadObject);

    doc = QJsonDocument(jsonPayloadObject);
    QHostAddress host(_arduino.getIpAddress());

    if(tcpSocket->state() == QAbstractSocket::UnconnectedState) {
        tcpSocket->connectToHost(host, _arduino.getPort());
    } else if (tcpSocket->state() == QAbstractSocket::ConnectedState) {
        if(tcpSocket->isValid())
            tcpSocket->write(doc.toJson());
        else
            printf("\nInvalid socket can;t write.");
    }
}

void SocketClient::onErrorOccured(QTcpSocket::SocketError socketError) {
    printf("\n %s", qUtf8Printable(tcpSocket->errorString()));
}

void SocketClient::onSocketStateChange() {
    printf("\nClient Socket State changed");

    switch (tcpSocket->state()) {
        case QAbstractSocket::UnconnectedState:
            break;
        case QAbstractSocket::HostLookupState:
            break;
        case QAbstractSocket::ConnectingState:
            break;
        case QAbstractSocket::ConnectedState:
            writeData();
            break;
        case QAbstractSocket::BoundState:
            break;
        case QAbstractSocket::ListeningState:
            break;
        case QAbstractSocket::ClosingState:
            reset();
            break;
    }
}

void SocketClient::onReadyRead() {
    const QByteArray block = tcpSocket->readAll();
    printf("\nGot data from connected client = %s", qUtf8Printable(block));
    emit receivedTcpReply(block);
}

void SocketClient::writeData() {
    if(doc.isEmpty()) {
        printf("\nDoc is empty, nothing to write.");
    } else {
        QByteArray block;
        QDataStream out(&block, QIODevice::ReadWrite);
        out.setVersion(QDataStream::Qt_5_15);

        out << quint32(doc.toJson().size());
        out << doc.toJson();

        tcpSocket->write(block);
    }
}

void SocketClient::reset() {
    //tcpSocket->deleteLater();
}

