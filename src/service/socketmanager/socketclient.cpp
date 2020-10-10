#include <QtNetwork/QHostAddress>
#include <QtCore/QDataStream>
#include "socketclient.h"

SocketClient::SocketClient(QObject *parent) : QObject(parent) {
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &SocketClient::onErrorOccured);
    connect(tcpSocket, &QTcpSocket::stateChanged, this, &SocketClient::onSocketStateChange);
    connect(tcpSocket, &QIODevice::readyRead, this, &SocketClient::onReadyRead);
}

void SocketClient::requestFullState(const Arduino &_arduino) {
    QJsonObject jsonPayloadObject;
    ReplyWithCode replyCode = ReplyWithCode::FULL_STATE_RPLY;
    jsonPayloadObject["replyCode"] = replyCode;

    QHostAddress host(_arduino.getIpAddress());
    tcpSocket->connectToHost(host, _arduino.getPort());

    doc = QJsonDocument(jsonPayloadObject);
}

void SocketClient::requestToggleRelay(const Arduino &_arduino, int relayId) {
    QJsonObject jsonPayloadObject;
    ReplyWithCode replyCode = ReplyWithCode::FULL_STATE_RPLY;
    jsonPayloadObject["replyCode"] = replyCode;
    jsonPayloadObject["toggleRelayId"] = relayId;

    QHostAddress host(_arduino.getIpAddress());
    tcpSocket->connectToHost(host, _arduino.getPort());

    doc = QJsonDocument(jsonPayloadObject);
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
        printf("\nDoc is empty, nothiing to write.");
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

