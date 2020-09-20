#ifndef BSF_NETWORKSERVICE_H
#define BSF_NETWORKSERVICE_H


#include <domain/iodevice.h>
#include <domain/arduino.h>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <service/requestmanager/requestmanager.h>

class NetworkService : public QObject {

    Q_OBJECT

private:
    RequestManager requestManager;
    QByteArray payload;
    Arduino arduino;
    QNetworkReply *reply = nullptr;
    void procesJsonPayload();
    void requestPayload(const QUrl& url);

public:
    explicit NetworkService(QObject *parent);
    void requestPayload(const Arduino &arduino, const QUrl& url);

public slots:
    void onAnswerRequestManager(const QByteArray &);
    void onReceiveRequestError(QNetworkReply::NetworkError);

signals:
    void sendArduinoWithNewStates(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};


#endif //BSF_NETWORKSERVICE_H
