#include "service/iodeviceservice.h"

#include <utility>

IODeviceService::IODeviceService(QObject *parent) : QObject(parent) {
    deviceController = new DeviceController(this);
}

QList<DeviceForm *> IODeviceService::createArduinoDeviceWidgetList(QWidget *parent) {
    return deviceController->createDeviceWidgets(parent);
}

void IODeviceService::createDeviceActionForm(DeviceActionForm * form) {
    deviceController->createDeviceActionForm(form);
}

void IODeviceService::createIODeviceForm(IODeviceForm *form, Arduino& arduino) {
    deviceController->createIODeviceForm(form, arduino);
}



