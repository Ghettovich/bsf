
#ifndef BSF_TCPSERVER_H
#define BSF_TCPSERVER_H

#include <QObject>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <arduino.h>

class LocalTcpServer : public QObject {
    Q_OBJECT

public:
    explicit LocalTcpServer(QObject *parent = nullptr);

public slots:
    void onNewConnection();
    void onReadyReadTcpPayload();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onSocketErrorOccured(QAbstractSocket::SocketError socketError);

signals:
    void receivedSocketData(const QByteArray &data);

private:
    QTcpServer tcpServer;
    QList<QTcpSocket*>  _sockets;
    QDataStream in;
    quint32 blockSize;

};


#endif //BSF_TCPSERVER_H
