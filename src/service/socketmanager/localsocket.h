
#ifndef BSF_LOCALSOCKET_H
#define BSF_LOCALSOCKET_H

#include <QObject>
#include <QtCore/QDataStream>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class LocalSocket : public QObject {
    Q_OBJECT

public:
    explicit LocalSocket(QObject *parent);

public slots:
    void onNewConnection();
    void onReadyReadTcpPayload();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onSocketErrorOccured(QAbstractSocket::SocketError socketError);

private:
    QTcpServer tcpServer;
    QList<QTcpSocket*>  _sockets;
    QDataStream in;
    quint32 blockSize;

};


#endif //BSF_LOCALSOCKET_H
