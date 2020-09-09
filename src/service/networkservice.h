#ifndef BSF_NETWORKSERVICE_H
#define BSF_NETWORKSERVICE_H


#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class NetworkService : public QObject {

    Q_OBJECT

private:
    Arduino *arduino = nullptr;
    QNetworkReply *reply = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    void procesJsonPayload();

public:
    explicit NetworkService(QObject *parent);
    void requestPayload(const QUrl& url);
    void requestPayload(Arduino* arduino);

public slots:
    void httpReadyRead();
    void httpError();

signals:
    void sendIODeviceListWithNewStates(const QVector<IODevice *>&);
    void sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, QVector<IODevice *>);
};


#endif //BSF_NETWORKSERVICE_H
