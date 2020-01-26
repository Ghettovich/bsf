#ifndef BSF_NETWORKSERVICE_H
#define BSF_NETWORKSERVICE_H


#include <domain/iodevice.h>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class NetworkService : public QObject {

    Q_OBJECT

private:
    QNetworkReply *reply = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;

    void procesJsonPayload();

public:
    explicit NetworkService(QObject *parent);
    void requestPayload(const QUrl& url);

public slots:
    void httpReadyRead();
    void httpError();

signals:
    void sendIODeviceListWithNewStates(QVector<IODevice *>);

};


#endif //BSF_NETWORKSERVICE_H
