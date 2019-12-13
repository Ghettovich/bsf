#ifndef BSF_IODEVICEPAYLOAD_H
#define BSF_IODEVICEPAYLOAD_H

#include <QtCore/qlist.h>
#include "iodevice.h"

class IODevicePayload {

public:
    QList<IODevice *> transformPayloadToIODeviceList(QByteArray payload);

};
#endif //BSF_IODEVICEPAYLOAD_H
