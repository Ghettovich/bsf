#include <QtWidgets/QHBoxLayout>
#include <utility>
#include <data/dbmanager.h>
#include "incl/ui/forms/devicemanager.h"
#include "incl/ui/forms/deviceform.h"

void DeviceManager::createDeviceWidgets() {
    deviceHbox = new QHBoxLayout;
    arduinos = dbManager.getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (arduino a : arduinos) {
        auto *deviceForm = new DeviceForm(*this);
        qDebug("%s", qUtf8Printable("loop entered"));
        deviceHbox->addWidget(deviceForm);
        deviceForm->initWidget(a);
    }
}

void DeviceManager::updateArduinoDevice(const arduino& arduinoDevice) {
    qDebug("%s", qUtf8Printable("update method called in device manager"));
    dbManager.updateArduino(arduinoDevice);
}

