#include "iodeviceformfactory.h"

#include <domain/iodevicetype.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/detectionsensorform.h>

QWidget *IODeviceFormFactory::createIODeviceForm(int deviceType, QWidget * _parent, IODevice& ioDevice) {
    if (deviceType == IODeviceType::DETECTIONSENSOR) {
        return new DetectionSensorForm(_parent, ioDevice);
    } else if (deviceType == IODeviceType::RELAY) {
        return new RelayForm(_parent, ioDevice);
    }
    return nullptr;
}

QWidget *IODeviceFormFactory::createWeightSensorForm(QWidget * _parent, WeightCensor& weightSensor) {
    return new WeightSensorForm(_parent, weightSensor);
}
