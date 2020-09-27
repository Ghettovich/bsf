#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <domain/arduino.h>
#include <domain/detectionsensor.h>
#include <domain/relay.h>
#include <domain/weightcensor.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload : public QObject {

    Q_OBJECT

public:
    enum ARDUINO_TYPE {
        UNKOWN = 0, BIN_LIFT = 1, WEIGHT_STATION = 2
    };
    Q_ENUM(ARDUINO_TYPE);

    static void updateArduinoWithPayload(int&, Arduino::ARDUINO_STATE&, QVector<IODevice *>&, const QByteArray&);
    static ARDUINO_TYPE identifyArduinoWithId(int arduinoId);
    static Arduino::ARDUINO_STATE identifyArduinoState(int state);
    static void parseIODeviceItemsInPayload(QJsonDocument &, QVector<IODevice *>&);
    static bool validateJsonDocument(QJsonDocument&);
    static IODevice *parseItemWeightStation(QJsonDocument&);

};
#endif //BSF_TRANSFORMPAYLOAD_H
