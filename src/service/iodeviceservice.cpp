#include "service/iodeviceservice.h"

IODeviceService::IODeviceService(QObject *parent) : QObject(parent) {
    deviceController = new DeviceController(this);
}

QList<DeviceForm *> IODeviceService::createArduinoDeviceWidgetList(QWidget *parent) {
    return deviceController->createDeviceWidgets(parent);
}

DeviceActionForm * IODeviceService::createDeviceActionForm(QWidget *parent) {
    return deviceController->createDeviceActionForm(parent);
}

IODeviceForm * IODeviceService::createIODeviceForm(QWidget *parent) {
    return deviceController->createIODeviceForm(parent);
}



