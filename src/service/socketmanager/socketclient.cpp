#include <QtNetwork/QHostAddress>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include "socketclient.h"

SocketClient::SocketClient(QObject *parent) : QObject(parent) {
    tcpSocket = new QTcpSocket(this);

    connect(tcpSocket, &QTcpSocket::errorOccurred, this, &SocketClient::onErrorOccured);
    connect(tcpSocket, &QTcpSocket::stateChanged, this, &SocketClient::onSocketStateChange);
}

void SocketClient::requestFullState(const Arduino &_arduino) {
    ReplyWithCode replyCode = ReplyWithCode::FULL_STATE_RPLY;
    jsonPayloadObject["replyCode"] = replyCode;

    QHostAddress host(_arduino.getIpAddress());
    tcpSocket->connectToHost(host, _arduino.getPort());
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
            break;
    }
}

void SocketClient::writeData() {
    QJsonDocument doc(jsonPayloadObject);
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_15);

    out << quint32(doc.toJson().size());
    out << doc.toJson();

    connect(tcpSocket, &QTcpSocket::disconnected, tcpSocket, &QTcpSocket::deleteLater);

    tcpSocket->write(block);
}

