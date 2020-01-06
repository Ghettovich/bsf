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
    void requestIODeviceState(const QString &url, IODevice *ioDevice);

private:
    IODevice *ioDevice = nullptr;
    QNetworkReply *reply = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    IODeviceRepository *ioDeviceRepository = nullptr;
    void processJsonPayload();
    void updateIODevicesWithDto(const QList<IODeviceDTO *>& ioDeviceDTOList);
    void processDatagram(const QByteArray &data);

public slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();

signals:
    void onReceiveIODeviceState(IODeviceState state);
    void onSendIODeviceDtoList(QList<IODeviceDTO *> dtoList);

};
#endif //BSF_PAYLOADSERVICE_H
