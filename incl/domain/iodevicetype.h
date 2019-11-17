#ifndef BSF_IODEVICETYPE_H
#define BSF_IODEVICETYPE_H

#include <QtCore/QString>

struct IODeviceType {
    int id;
    QString  type;
    QString  description;
};

enum IODeviceTypeEnum {WEIGHTCENSOR = 1, DETECTIONCENSOR = 2, RELAYBLOCK = 3};
#endif //BSF_IODEVICETYPE_H
