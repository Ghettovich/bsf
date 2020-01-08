#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <incl/factory/networkmanagerfactory.h>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>
#include <incl/domain/iodevice.h>
#include <incl/dto/iodevicedto.h>
#include <incl/statemachine/pavementstateobject.h>

class PayloadService : public QObject {
    Q_OBJECT

public:
    PayloadService();
    void setStateObject(PavementStateObject *_stateObject);
    void requestStatePayload(const QString &url = "");
    void requestIODeviceState(const QString &url, IODevice *ioDevice);

private:
    PavementStateObject *stateObject = nullptr;
    IODevice *ioDevice = nullptr;
    QNetworkReply *reply = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    void processJsonPayload();
    void updateIODevicesWithDto(const QList<IODeviceDTO *>& ioDeviceDTOList);
    void processDatagram(const QByteArray &data);

public slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();


    //ToDo: re evaluate signals io device form and state tab
signals:
    void onReceiveIODeviceState(IODeviceState state);
    void onSendIODeviceDtoList(const QList<IODeviceDTO *> &dtoList);
    void onUpdateStateObject(const QList<IODeviceDTO *>& dtoList);
    void onUpdateStateMachineTab(const QList<IODeviceDTO *>&);

};
#endif //BSF_PAYLOADSERVICE_H
