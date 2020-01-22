#ifndef BSF_IODEVICEFORMFACTORY_H
#define BSF_IODEVICEFORMFACTORY_H

#include <domain/iodevice.h>
#include <domain/weightcensor.h>
#include <QtWidgets/QWidget>


class IODeviceFormFactory {

public:
    static QWidget * createIODeviceForm(int, QWidget *, IODevice&);
    static QWidget * createWeightSensorForm(QWidget *, WeightCensor&);
    static QWidget * createDeviceActiomForm(QWidget*);
    static QWidget * createIODeviceForm(QWidget*);
};
#endif //BSF_IODEVICEFORMFACTORY_H
