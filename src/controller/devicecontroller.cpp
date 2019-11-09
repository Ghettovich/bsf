#include <QtWidgets/QHBoxLayout>
#include <utility>
#include "incl/controller/devicecontroller.h"
#include "incl/ui/forms/deviceform.h"

void DeviceController::createDeviceWidgets() {
    deviceHbox = new QHBoxLayout;
    arduinos = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinos) {
        auto *deviceForm = new DeviceForm(*this);
        qDebug("%s", qUtf8Printable("loop entered"));
        deviceHbox->addWidget(deviceForm);
        deviceForm->initWidget(a);
    }
}

void DeviceController::updateArduinoDevice(const Arduino& arduinoDevice) {
    qDebug("%s", qUtf8Printable("update method called in device manager"));
    arduinoRepository->updateArduino(arduinoDevice);
}

