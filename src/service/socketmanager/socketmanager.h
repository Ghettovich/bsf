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

private:
    const int defaultPort = 6677;
    QUdpSocket udpSocket;
    void processDatagram(const QByteArray &payload);

public slots:
    void onConnectedWithHost();
    void onIncomingDatagrams();
    void onSocketErrorOccured();

signals:
    void hostFound();
    void receivedPayload(const QByteArray&);
};


#endif //BSF_SOCKETMANAGER_H
