#ifndef BSF_NETWORKSERVICE_H
#define BSF_NETWORKSERVICE_H


#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <service/requestmanager/requestmanager.h>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <service/socketmanager/socketclient.h>

class NetworkService : public QObject {

    Q_OBJECT

private:
    SocketClient client;
    Arduino arduino;

public:
    explicit NetworkService(QObject *parent);
    void requestPayload(const Arduino &arduino);
    void toggleRelay(const Arduino &_arduino, int relayId);

public slots:
    void onTcpReply(const QByteArray &data);
    void onReceiveRequestError(QNetworkReply::NetworkError);

signals:
    void sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};


#endif //BSF_NETWORKSERVICE_H
