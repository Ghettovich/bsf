#include "service/iodeviceservice.h"

IODeviceService::IODeviceService() {
    deviceController = new DeviceController();
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



