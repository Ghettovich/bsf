#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <dto/iodevicedto.h>
#include <dto/arduinodto.h>
#include <QtCore/QList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload {

public:
    static QList<IODeviceDTO *> transformJSONPayloadToDtoIODeviceList(const QByteArray& payload);
    static ArduinoDTO transformJSONPayloadToArduinoDto(const QByteArray& payload);
    static QList<IODeviceDTO *> transformPayloadToDtoIODeviceList(const QByteArray& payload);
    static IODeviceDTO *transformJSONPayloadToIODevice(int id, const QByteArray& byteArray);

};
#endif //BSF_TRANSFORMPAYLOAD_H
