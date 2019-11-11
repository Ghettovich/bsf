#ifndef SERVER_H
#define SERVER_H

// Server side implementation of UDP client-server model
#include <QTimer>
#include <QWidget>
#include <QtNetwork/QUdpSocket>

class Server : public QObject
{
Q_OBJECT

public:
    Server();
    QString getResponseMsg();
    QString getBroadcastedMsg();
    int getNrOfMessages();
    void setQbyteArrayBroadcastedMsg(const QByteArray &value);
    bool hasPendingDatagrams();

public slots:
    void readPendingDatagrams();
    void broadcastDatagram(quint16 portToListenOn);
    void broadcastDatagram(quint16 portToListenOn, const char *broadcastDatagramMsg);

private:
    int msgNr = 1;
    quint16 portListenOn = 12300;
    quint16 portBroadcastMsg = 0;
    QHostAddress hostAddress;
    QByteArray qbyteArrayResponseMsg = nullptr;
    QByteArray qbyteArrayBroadcastedMsg = nullptr;
    QUdpSocket *udpSocket = nullptr;
    void initSocket();
};

#endif // SERVER_H
