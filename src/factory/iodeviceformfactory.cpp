#include "iodeviceformfactory.h"

DeviceActionForm *IODeviceFormFactory::createDeviceActiomForm(QWidget *parent) {
    return new DeviceActionForm(parent, Qt::Widget);
}

IODeviceForm *IODeviceFormFactory::createIODeviceForm(QWidget *parent) {
    return new IODeviceForm(parent, Qt::Widget);
}
