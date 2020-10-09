
#ifndef BSF_SOCKETCLIENT_H
#define BSF_SOCKETCLIENT_H


#include <domain/arduino.h>
#include <QtCore/QObject>
#include <QtCore/QJsonObject>
#include <QtNetwork/QTcpSocket>

class SocketClient : public QObject {

    Q_OBJECT

public:
    enum ReplyWithCode {
        FULL_STATE_RPLY,
        RELAY_STATE_RPLY,
        DETECTION_STATE_RPLY
    };
    Q_ENUM(ReplyWithCode);

    explicit SocketClient (QObject *parent = nullptr);
    void requestFullState(const Arduino &arduino);

public slots:
    void onErrorOccured(QTcpSocket::SocketError socketError);
    void onSocketStateChange();

private:
    QTcpSocket *tcpSocket;
    QJsonObject jsonPayloadObject;

    void writeData();
};


#endif //BSF_SOCKETCLIENT_H
