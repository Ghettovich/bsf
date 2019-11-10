#ifndef SERVER_H
#define SERVER_H

// Server side implementation of UDP client-server model
#include <QTimer>
#include <QWidget>
#include <QtNetwork/QUdpSocket>

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

class Server : public QObject
{
Q_OBJECT

public:
    Server();
    QString getResponseMsg();
    QString getBroadcastedMsg();
    int getNrOfMessages();
    void setQbyteArrayBroadcastedMsg(const QByteArray &value);

public slots:
    void processPendingDatagrams();
    void broadcastDatagram(quint16 portToListenOn);
    void broadcastDatagram(quint16 portToListenOn, const char *broadcastDatagramMsg);

private:
    int msgNr = 1;
    quint16 portListenOn = 12300;
    quint16 portBroadcastMsg = 0;

    QByteArray qbyteArrayResponseMsg = nullptr;
    QByteArray qbyteArrayBroadcastedMsg = nullptr;
    QUdpSocket *udpSocket = nullptr;
    void initSocket();
};

#endif // SERVER_H
