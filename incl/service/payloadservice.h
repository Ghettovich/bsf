#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <incl/factory/networkmanagerfactory.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>
#include <incl/domain/iodevice.h>
#include <incl/dto/iodevicedto.h>
#include <incl/repo/iodevicerepo.h>

class PayloadService : public QObject {
    Q_OBJECT

public:
    explicit PayloadService(QObject *parent);
    void requestStatePayload(const QString &url = "");
    void requestIODeviceState(IODevice *_ioDevice, const QString &url);

private:
    IODevice *ioDevice;
    QList<IODevice *> ioDeviceList;
    QNetworkReply *reply = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    IODeviceRepository *ioDeviceRepository = nullptr;
    void processJsonPayload();

private slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();
};
#endif //BSF_PAYLOADSERVICE_H
