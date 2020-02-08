#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <domain/arduino.h>
#include <domain/detectionsensor.h>
#include <domain/relay.h>
#include <domain/weightcensor.h>
#include <dto/iodevicedto.h>
#include <dto/arduinodto.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload {

public:
    static ArduinoDTO transformJSONPayloadToArduinoDto(const QByteArray& payload);
    static IODeviceDTO *transformJSONPayloadToIODevice(int id, const QByteArray& byteArray);
    static QList<IODeviceDTO *> transformJSONPayloadToDtoIODeviceList(const QByteArray& payload);
    static QList<IODeviceDTO *> transformPayloadToDtoIODeviceList(const QByteArray& payload);

    static QVector<IODevice *> transformPayloadToIODeviceList(const QByteArray&);
    static void updateArduinoWithPayload(Arduino * arduino, QVector<IODevice *>& ioDeviceList, const QByteArray&);

private:
    static void parseIODeviceItemsInPayload(QJsonArray&, QVector<IODevice *>&);
    static void identifyArduinoState(Arduino *, int state);

};
#endif //BSF_TRANSFORMPAYLOAD_H
