#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <QtWidgets/QWidget>


class IODeviceFormFactory {

public:
    static QWidget * createIODeviceForm(int deviceType, IODevice *);
    static QWidget * createWeightSensorForm(WeightCensor*);
};
#endif //BSF_IODEVICEFORMFACTORY_H
