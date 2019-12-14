#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <incl/factory/networkmanagerfactory.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QUdpSocket>
#include <QJsonObject>
#include <incl/domain/iodevice.h>
#include <incl/dto/iodevicedto.h>
#include <incl/repo/iodevicerepo.h>

class PayloadService : public QObject {
    Q_OBJECT

public:
    explicit PayloadService(QObject *parent);
    void requestFullStatePayload();
    void requestFullStatePayload(int ioDeviceId, IODevice *ioDevice);
    QJsonObject requestIODeviceSateJSON(int ioDeviceId);
    QList<IODevice *> createIODeviceListCurrentState();

private:
    //QList<IODeviceDTO *> ioDeviceDTOList;
    //QList<IODevice *> ioDeviceListCurrentState;
    QNetworkReply *reply = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    IODeviceRepository *ioDeviceRepository = nullptr;

private slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();
};
#endif //BSF_PAYLOADSERVICE_H
