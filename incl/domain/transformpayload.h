#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <QtCore/QObject>
#include <QtCore/qlist.h>
#include <incl/dto/iodevicedto.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class TransformPayload : public QObject {

public:
    static QJsonObject requestJsonObjectIODevice(int id, const QByteArray& byteArray);
    static QList<IODeviceDTO *> transformPayloadToDtoIODeviceList(const QByteArray& payload);
    static QList<IODeviceDTO *> transformJSONPayloadToDtoIODeviceList(const QByteArray& payload);

};
#endif //BSF_TRANSFORMPAYLOAD_H
