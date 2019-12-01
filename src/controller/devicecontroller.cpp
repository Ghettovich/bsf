#include "incl/controller/devicecontroller.h"

DeviceController::DeviceController(QWidget *parent) {
    parentWidget = parent;
    arduinoRepository = new ArduinoRepository;
}

QList<DeviceForm *> DeviceController::createDeviceWidgets() {
    QList<DeviceForm *> widgetList;
    arduinos = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinos) {
        auto *deviceForm = new DeviceForm(parentWidget);
        deviceForm->initWidget(a);
        widgetList.append(deviceForm);
    }

    return widgetList;
}

DeviceActionForm *DeviceController::createDeviceActionForm() {
    auto *deviceActionForm = new DeviceActionForm(parentWidget);
    return deviceActionForm;
}

