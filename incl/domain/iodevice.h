#ifndef IODEVICE_H
#define IODEVICE_H

#include <QtCore/QString>

struct IODevice {
    int id;
    int arduino_id;
    int type_id;
    QString desc;
};

#endif // IODEVICE_H


