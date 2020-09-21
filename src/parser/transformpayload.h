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

class TransformPayload {

public:
    static void updateArduinoWithPayload(int&, Arduino::ARDUINO_STATE&, QVector<IODevice *>&, const QByteArray&);

private:
    static void parseIODeviceItemsInPayload(QJsonArray&, QVector<IODevice *>&);
    static void identifyArduinoState(int, Arduino::ARDUINO_STATE &);

};
#endif //BSF_TRANSFORMPAYLOAD_H
