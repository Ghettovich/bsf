#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <domain/weightcensor.h>
#include <domain/recipe.h>
#include <domain/arduino.h>
#include <service/socketmanager/socketmanager.h>
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
    void broadcastRecipe(Recipe, int, const QString&, int port = 6678);

private:
    QNetworkDatagram datagram;
    SocketManager udpSocketManager;

public slots:
    void onReceiveError();
    void onFoundHost();
    void onParsePayload(const QByteArray&);

signals:
    void receivedError();
    void foundArduinoHost();
    void receivedIODevicesWithNewState(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};
#endif //BSF_PAYLOADSERVICE_H
