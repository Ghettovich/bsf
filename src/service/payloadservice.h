#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <domain/iodevice.h>
#include <domain/recipe.h>
#include <domain/arduino.h>
//#include <statemachine/pavementstateobject.h>
#include <QObject>
#include <QtCore/QList>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkAccessManager>

class PayloadService : public QObject {

Q_OBJECT

public:
    enum StateReplyWeightStation {
        WEIGHT_STATION_IDLE, PARSED_RECIPE_SUCCESSFULL, UPDATE_WEIGHT_SENSOR
    };
    Q_ENUM(StateReplyWeightStation);

    explicit PayloadService(QObject *parent);
//    void setStateObject(PavementStateObject *_stateObject);
    //void requestStatePayload(const QString &url = "");
    void broadcastRecipe(Recipe, const QString&, int port = 6678);

private:
    //Arduino *arduino;
//    PavementStateObject *stateObject = nullptr;
    //IODevice *ioDevice = nullptr;

    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketWeightStation = nullptr;
    void processJsonPayload();
    //void updateIODevicesWithDto(const QList<IODeviceDTO *>& ioDeviceDTOList);
    void processDatagram(const QByteArray &data);
    void processDatagramWeightStation(const QByteArray &data);

public slots:
    void onIncomingDatagrams();
    void onIncomingDatagramsWeightStation();


    //ToDo: re evaluate signals io device form and state tab
//signals:
//    void onReceiveIODeviceState(int state);
//    void onUpdateStateObject(QList<IODeviceDTO> dtoList);
//    void onUpdateStateObject(IODeviceDTO dto);
//    void onReceiveWeightStationReply(const QByteArray &);
//    void onReceiveWeightSensorData(int, int, int);

};
#endif //BSF_PAYLOADSERVICE_H
