#include "tcpserver.h"
#include <QtNetwork/QHostAddress>

LocalTcpServer::LocalTcpServer(QObject *parent) : QObject(parent) {
    tcpServer.listen(QHostAddress::AnyIPv4, 5001);

    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

void LocalTcpServer::onReadyReadTcpPayload() {
    auto sender = dynamic_cast<QTcpSocket*>(QObject::sender());
    const QByteArray data = sender->readAll();

    printf("\n (data2) %s", qUtf8Printable(data));
    emit receivedSocketData(data);
}

void LocalTcpServer::onSocketErrorOccured(QAbstractSocket::SocketError socketError) {

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

void LocalTcpServer::onNewConnection() {
    QByteArray block;
    QDataStream writer(&block, QIODevice::WriteOnly);

    printf("\nNew connection");
    QTcpSocket *clientSocket = tcpServer.nextPendingConnection();
    connect(clientSocket, &QIODevice::readyRead, this, &LocalTcpServer::onReadyReadTcpPayload);
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
//    for (QTcpSocket* socket : _sockets) {
//        printf("\nBuffer size = %d", (int)socket->size());
//        writer.writeBytes(socket->readAll(), socket->size());
//        //socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
//    }
}

void LocalTcpServer::onSocketStateChanged(QAbstractSocket::SocketState socketState) {
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        auto sender = dynamic_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}
