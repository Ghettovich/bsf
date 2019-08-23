#ifndef SERVER_H
#define SERVER_H

// Server side implementation of UDP client-server model
#include <QUdpSocket>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QUdpSocket;
QT_END_NAMESPACE

#define PORT 9900
#define MAXLINE 1024

class Server : public QObject
{
Q_OBJECT

public:
    explicit Server();
    //QUdpSocket* createNewSocket(quint16 port);

private slots:
    void processPedingDatagrams();

private:    
    QUdpSocket *udpSocket = nullptr;
    void initSocket();
};

#endif // SERVER_H
