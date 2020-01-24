#include "iodeviceformfactory.h"

DetectionSensorForm *IODeviceFormFactory::createDetectionSensorForm(QWidget * _parent, IODevice& ioDevice) {
    return new DetectionSensorForm(_parent, Qt::Widget, ioDevice);
}

RelayForm *IODeviceFormFactory::createRelayForm(QWidget * parent, IODevice & ioDevice) {
    return new RelayForm(parent, Qt::Widget, ioDevice);
}

WeightSensorForm *IODeviceFormFactory::createWeightSensorForm(QWidget * _parent, WeightCensor& weightSensor) {
    return new WeightSensorForm(_parent, Qt::Widget, weightSensor);
}

DeviceActionForm *IODeviceFormFactory::createDeviceActiomForm(QWidget *parent) {
    return new DeviceActionForm(parent, Qt::Widget);
}

IODeviceForm *IODeviceFormFactory::createIODeviceForm(QWidget *parent) {
    return new IODeviceForm(parent, Qt::Widget);
}
