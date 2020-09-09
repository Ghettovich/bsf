#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <domain/weightcensor.h>
#include <domain/recipe.h>
#include <domain/arduino.h>
#include <QObject>
#include <QtCore/QVector>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QUdpSocket>

class PayloadService : public QObject {

Q_OBJECT

public:
    enum StateReplyWeightStation {
        WEIGHT_STATION_IDLE, PARSED_RECIPE_SUCCESSFULL, UPDATE_WEIGHT_SENSOR
    };
    Q_ENUM(StateReplyWeightStation);

    explicit PayloadService(QObject *parent);
    void broadcastRecipe(Recipe, const QString&, int port = 6678);

private:
    const int arduino1UdpPort = 6677, arduino2UdpPort = 6678;
    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketWeightStation = nullptr;
    void processDatagram(const QByteArray &data);
    void processDatagramWeightStation(const QByteArray &data);

public slots:
    void onIncomingDatagrams();
    void onIncomingDatagramsWeightStation();

signals:
    //void receivedIODevicesWithNewState2(QVector<IODevice *>);
    void receivedIODevicesWithNewState(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};
#endif //BSF_PAYLOADSERVICE_H
