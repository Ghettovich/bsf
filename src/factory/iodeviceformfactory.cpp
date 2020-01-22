#include "iodeviceformfactory.h"

#include <domain/iodevicetype.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/detectionsensorform.h>
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

QWidget *IODeviceFormFactory::createIODeviceForm(int deviceType, QWidget * _parent, IODevice& ioDevice) {
    if (deviceType == IODeviceType::DETECTIONSENSOR) {
        return new DetectionSensorForm(_parent, Qt::Widget, ioDevice);
    } else if (deviceType == IODeviceType::RELAY) {
        return new RelayForm(_parent, Qt::Widget, ioDevice);
    }
    return nullptr;
}

QWidget *IODeviceFormFactory::createWeightSensorForm(QWidget * _parent, WeightCensor& weightSensor) {
    return new WeightSensorForm(_parent, Qt::Widget, weightSensor);
}

QWidget *IODeviceFormFactory::createDeviceActiomForm(QWidget *parent) {
    return new DeviceActionForm(parent, Qt::Widget);
}

QWidget *IODeviceFormFactory::createIODeviceForm(QWidget *parent) {
    return new IODeviceForm(parent, Qt::Widget);
}
