#ifndef BSF_UDPSERVER_H
#define BSF_UDPSERVER_H

#include <QtCore/QObject>
#include <QUdpSocket>

class UdpServer : public QObject {
    Q_OBJECT

public:
    explicit UdpServer(QObject *parent);
    void broadcastDatagram(QNetworkDatagram&);

    int getPort() const;

private:
    const int port = 6699;
    QUdpSocket udpServerSocket;

public slots:
    void onIncomingDatagrams();
    void onSocketErrorOccured();
    void onConnectedWithHost();
    void onConnectionEstablished();

signals:
    void receivedPayload(const QByteArray&);
    void receivedErrorOccured();
    void connectedToHost();
    void connectionEstablished();
};


#endif //BSF_UDPSERVER_H
