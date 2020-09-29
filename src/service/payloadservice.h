#ifndef BSF_PAYLOADSERVICE_H
#define BSF_PAYLOADSERVICE_H

#include <domain/weightcensor.h>
#include <domain/recipe.h>
#include <domain/arduino.h>
#include <parser/transformpayload.h>
#include <service/socketmanager/socketmanager.h>
#include <QObject>
#include <QtCore/QVector>
#include <QtNetwork/QUdpSocket>

class PayloadService : public QObject {

Q_OBJECT

public:
    explicit PayloadService(QObject *parent);
    void broadcastRecipe(Recipe recipe,int arduinoId, const QString &host, int port);

private:
    SocketManager udpSocketManager;
    TransformPayload transformPayload;
    void parsePayload(int, TransformPayload::ARDUINO_TYPE, Arduino::ARDUINO_STATE, QJsonDocument&);

public slots:
    void onReceiveError();
    void onParsePayload(const QByteArray&);

signals:
    void receivedError();
    void receivedUpdateForWeightSensor(IODevice*, Arduino::ARDUINO_STATE);
    void receivedIODevicesWithNewState(int, Arduino::ARDUINO_STATE, const QVector<IODevice *>&);
};
#endif //BSF_PAYLOADSERVICE_H
