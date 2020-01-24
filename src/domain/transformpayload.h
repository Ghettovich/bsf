#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <dto/iodevicedto.h>
#include <dto/arduinodto.h>
#include <domain/iodevice.h>
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
    static QVector<IODevice> transformPayloadToIODeviceList(const QByteArray&);

private:
    static void parseIODeviceItemsInPayload(QJsonArray&, QVector<IODevice>);

};
#endif //BSF_TRANSFORMPAYLOAD_H
