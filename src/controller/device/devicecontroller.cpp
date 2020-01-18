#include "devicecontroller.h"

DeviceController::DeviceController() {
    arduinoRepository = new ArduinoRepository;
}

QList<DeviceForm *> DeviceController::createDeviceWidgets(QWidget *parent) {
    QList<DeviceForm *> widgetList;
    QList<Arduino> arduinoList = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinoList) {
        qDebug("%s", qUtf8Printable("got arduino"));
        auto *deviceForm = new DeviceForm(parent);
        deviceForm->initWidget(a);
        widgetList.append(deviceForm);
    }

    return widgetList;
}

DeviceActionForm *DeviceController::createDeviceActionForm(QWidget *parent) {
    return new DeviceActionForm(parent);
    //return deviceActionForm;
}

IODeviceForm *DeviceController::createIODeviceForm(QWidget *parent) {
    return new IODeviceForm(parent);
}
