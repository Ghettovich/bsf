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
    void broadcastDatagram(const QNetworkDatagram&);
    int getDefaultPort() const;
    QString getSocketErrorMessage();

private:
    QUdpSocket udpSocket;
    void processDatagram(const QByteArray &payload);

public slots:
    void onIncomingDatagrams();
    void onSocketErrorOccured(QAbstractSocket::SocketError socketError);

signals:
    void arduinoNotFound();
    void receivedPayload(const QByteArray&);
    void receivedErrorOccured();
};


#endif //BSF_SOCKETMANAGER_H
