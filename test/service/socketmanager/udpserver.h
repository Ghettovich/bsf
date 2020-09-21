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
    QUdpSocket *udpServerSocket = nullptr;

public slots:
    void onIncomingDatagrams();

signals:
    void receivedPayload(const QByteArray&);
};


#endif //BSF_UDPSERVER_H
