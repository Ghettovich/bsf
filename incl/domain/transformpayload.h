#ifndef BSF_TRANSFORMPAYLOAD_H
#define BSF_TRANSFORMPAYLOAD_H

#include <QtCore/qlist.h>
#include <incl/dto/iodevicedto.h>


class TransformPayload {

public:
    static QList<IODeviceDTO *> transformPayloadToDtoIODeviceList(const QByteArray& payload);

};
#endif //BSF_TRANSFORMPAYLOAD_H
