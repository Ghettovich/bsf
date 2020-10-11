
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
        DETECTION_STATE_RPLY,
        EMPTY
    };
    Q_ENUM(ReplyWithCode);

    explicit SocketClient (QObject *parent = nullptr);
    void requestFullState(const Arduino &arduino, ReplyWithCode replyCode = FULL_STATE_RPLY);
    void requestToggleRelay(const Arduino &arduino, int relayId, ReplyWithCode replyCode = FULL_STATE_RPLY);
    void requestSetRecipe(const Arduino &arduino, Recipe recipe, ReplyWithCode replyCode = FULL_STATE_RPLY);

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
