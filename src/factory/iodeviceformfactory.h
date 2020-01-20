#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <QtWidgets/QWidget>


class IODeviceFormFactory {

public:
    static QWidget * createIODeviceForm(int, QWidget *, IODevice);
    static QWidget * createWeightSensorForm(QWidget *, WeightCensor);
};
#endif //BSF_IODEVICEFORMFACTORY_H
