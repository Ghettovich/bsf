#ifndef IODEVICE_H
#define IODEVICE_H

#include <QtCore/QString>
#include "arduino.h"
#include "action.h"
#include "iodevicetype.h"

struct IODevice {
    int id = 0;
    Arduino arduino;
    Action action;
    IODeviceType ioDeviceType;
};

#endif // IODEVICE_H


