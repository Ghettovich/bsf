#include "iodeviceformfactory.h"

#include <domain/iodevicetype.h>
#include <ui/forms/weightsensorform.h>
#include <ui/forms/relayform.h>
#include <ui/forms/detectionsensorform.h>

QWidget *IODeviceFormFactory::createIODeviceForm(int type, IODevice * ioDevice) {
    qDebug("%s", qUtf8Printable("created form from factory"));

    if (type == IODeviceType::DETECTIONSENSOR) {
        return new DetectionSensorForm(ioDevice);
    } else if (type == IODeviceType::RELAY) {
        return new RelayForm(ioDevice);
    }
    return nullptr;
}

QWidget *IODeviceFormFactory::createWeightSensorForm(WeightCensor * weightSensor) {
    return new WeightSensorForm(weightSensor);
}
