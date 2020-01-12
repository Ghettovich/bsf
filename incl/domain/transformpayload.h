#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <QtCore/QObject>
#include <QtCore/qlist.h>
#include <incl/dto/iodevicedto.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <incl/dto/arduinodto.h>

class TransformPayload : public QObject {

public:
    static QList<IODeviceDTO *> transformJSONPayloadToDtoIODeviceList(const QByteArray& payload);
    static ArduinoDTO transformJSONPayloadToArduinoDto(const QByteArray& payload);
    static QList<IODeviceDTO *> transformPayloadToDtoIODeviceList(const QByteArray& payload);
    static IODeviceDTO *transformJSONPayloadToIODevice(int id, const QByteArray& byteArray);

};
#endif //BSF_TRANSFORMPAYLOAD_H
