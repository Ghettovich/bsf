#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <incl/factory/networkmanagerfactory.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QUdpSocket>
#include <incl/domain/iodevice.h>

class PayloadService : public QObject {
    Q_OBJECT

public:
    explicit PayloadService(QObject *parent);
    void requestFullStatePayload();

private:
    QNetworkReply *reply = nullptr;
    //QHostAddress *qHostAddress = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;

private slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();
};
#endif //BSF_PAYLOADSERVICE_H
