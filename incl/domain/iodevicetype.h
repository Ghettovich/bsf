#ifndef BSF_IODEVICETYPE_H
#define BSF_IODEVICETYPE_H

#include <QtCore/QString>

struct IODeviceType {
    int id;
    QString  type;
    QString  description;
};

enum IODeviceTypeEnum {WEIGHTSENSOR = 1, DETECTIONSENSOR = 2, RELAY = 3};
#endif //BSF_IODEVICETYPE_H
