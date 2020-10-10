
#ifndef BSF_SOCKETCLIENT_H
#define BSF_SOCKETCLIENT_H


#include <domain/arduino.h>
#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
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
    void requestToggleRelay(const Arduino &arduino, int relayId);

public slots:
    void onErrorOccured(QTcpSocket::SocketError socketError);
    void onSocketStateChange();
    void onReadyRead();

signals:
    void receivedTcpReply(const QByteArray &data);

private:
    QTcpSocket *tcpSocket = nullptr;
    QJsonDocument doc;

    void writeData();
    void reset();
};


#endif //BSF_SOCKETCLIENT_H
