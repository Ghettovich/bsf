#ifndef BSF_SOCKETMANAGER_H
#define BSF_SOCKETMANAGER_H

#include <QObject>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>

static const int socketManagerPort = 6677;

class SocketManager : public QObject {

    Q_OBJECT

public:
    explicit SocketManager(QObject *parent);
    void broadcastDatagram(QNetworkDatagram&);
    void connectoToHost(const QHostAddress&, int port);
    bool isConnectedToHost();
    int getDefaultPort() const;
    QString getSocketErrorMessage();

private:
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
