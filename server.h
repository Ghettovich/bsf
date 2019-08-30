#ifndef SERVER_H
#define SERVER_H

// Server side implementation of UDP client-server model
#include <QTimer>
#include <QUdpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

//#define PORT 9900
//#define MAXLINE 1024

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
    quint16 portListenOn = 9900;
    quint16 portBroadcastMsg = 0;

    QByteArray qbyteArrayResponseMsg = nullptr;
    QByteArray qbyteArrayBroadcastedMsg = nullptr;
    QUdpSocket *udpSocket = nullptr;
    void initSocket();
};

#endif // SERVER_H
