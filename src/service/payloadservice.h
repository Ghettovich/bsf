#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>
#include <factory/networkmanagerfactory.h>
#include <statemachine/pavementstateobject.h>

class PayloadService : public QObject {
    Q_OBJECT

    enum StateReplyWeightStation {
        WEIGHT_STATION_IDLE = 0, PARSED_RECIPE_SUCCESSFULL = 1, UPDATE_WEIGHT_SENSOR = 2
    };

    enum StateReplyEnum {
        READY = 0, LIFT_ASC = 1, LIFT_DESC = 2, BIN_LOADING = 3, BIN_DUMPING = 4, LIFT_STUCK = 90, BIN_STUCK = 91
    };

public:
    PayloadService();
    void setStateObject(PavementStateObject *_stateObject);
    void requestStatePayload(const QString &url = "");
    void requestStatePayload(Arduino _arduino, const QString &url = "");
    void requestIODeviceState(const QString &url, IODevice *ioDevice);
    void broadcastRecipe(Recipe *recipe, Arduino _arduino);

private:
    Arduino *arduino;
    PavementStateObject *stateObject = nullptr;
    IODevice *ioDevice = nullptr;
    QNetworkReply *reply = nullptr;
    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketWeightStation = nullptr;
    QNetworkAccessManager *networkAccessManager = nullptr;
    void processJsonPayload();
    void updateIODevicesWithDto(const QList<IODeviceDTO *>& ioDeviceDTOList);
    void processDatagram(const QByteArray &data);
    void processDatagramWeightStation(const QByteArray &data);

public slots:
    void httpReadyRead();
    void httpError();
    void onIncomingDatagrams();
    void onIncomingDatagramsWeightStation();


    //ToDo: re evaluate signals io device form and state tab
signals:
    void onReceiveIODeviceState(IODeviceState state);
    //void onSendIODeviceDtoList(const QList<IODeviceDTO *> &dtoList);
    void onUpdateStateObject(const QList<IODeviceDTO *>& dtoList);
    //void onUpdateStateMachineTab(const QList<IODeviceDTO *>&);
    void onReceiveWeightStationReply(const QByteArray &);
    void onReceiveWeightSensorData(int, int, int);

};
#endif //BSF_PAYLOADSERVICE_H
