#ifndef BSF_SOCKETMANAGER_H
#define BSF_SOCKETMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>

class SocketManager : public QObject {

    Q_OBJECT

public:
    explicit SocketManager(QObject *parent);
    void broadcastDatagram(QNetworkDatagram&);
    void connectoToHost(QHostAddress&, int port);
    bool isConnectedToHost();
    int getDefaultPort() const;

private:
    const int defaultPort = 6677;
    QUdpSocket udpSocket;
    void processDatagram(const QByteArray &payload);

public slots:
    void onConnectedWithHost();
    void onIncomingDatagrams();
    void onSocketErrorOccured();
    void onConnectionEstablished();

signals:
    void connectedToHost();
    void connectionEstablished();
    void receivedPayload(const QByteArray&);
    void receivedErrorOccured();
};


#endif //BSF_SOCKETMANAGER_H
