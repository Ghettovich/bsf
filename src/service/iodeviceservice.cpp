#include "incl/service/iodeviceservice.h"

IODeviceService::IODeviceService(QWidget *parentWidget) :
        QObject(parentWidget) {
    //REPO
    deviceController = new DeviceController(parentWidget);

}

QList<DeviceForm *> IODeviceService::createArduinoDeviceFormList() {
    return deviceController->createDeviceWidgets();
}

DeviceActionForm *IODeviceService::createDeviceActionForm() {
    return deviceController->createDeviceActionForm();
}

