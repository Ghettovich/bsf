
#include <QtNetwork/QHostAddress>
#include "localsocket.h"

LocalSocket::LocalSocket(QObject *parent) : QObject(parent) {
    tcpServer.listen(QHostAddress::AnyIPv4, 5001);

    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void LocalSocket::onReadyReadTcpPayload() {


    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write("Kurwa");
    }

    printf("%s", qUtf8Printable(datas));
}

void LocalSocket::onSocketErrorOccured(QAbstractSocket::SocketError socketError) {

    switch (socketError) {
        case QAbstractSocket::HostNotFoundError:
            printf("The host was not found. Please make sure "
                   "that the server is running and that the "
                   "server name is correct.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            printf("Local Fortune Client"
                          "The connection was refused by the peer. "
                          "Make sure the fortune server is running, "
                          "and check that the server name is correct.");
            break;
        default:
            printf("Local Fortune Client. The following error occurred: %s.",
                   qUtf8Printable(tcpServer.errorString()));
    }
}

void LocalSocket::onNewConnection() {
    printf("\nNew connection");
    QTcpSocket *clientSocket = tcpServer.nextPendingConnection();
    connect(clientSocket, &QIODevice::readyRead, this, &LocalSocket::onReadyReadTcpPayload);
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }
}

void LocalSocket::onSocketStateChanged(QAbstractSocket::SocketState socketState) {
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}
