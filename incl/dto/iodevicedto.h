#ifndef BSF_IODEVICEDTO_H
#define BSF_IODEVICEDTO_H

#include <QtCore/qchar.h>

struct IODeviceDTO {
    int id;
    int actionId;
    int typeId;
    bool isLOW = false;
};
#endif //BSF_IODEVICEDTO_H
