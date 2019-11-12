#include <QObject>
#include <QtWidgets/QHBoxLayout>
#include <incl/controller/devicecontroller.h>
#include <incl/ui/forms/deviceform.h>

DeviceController::DeviceController() = default;

void DeviceController::createDeviceWidgets() {
    deviceHbox = new QHBoxLayout;
    arduinos = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinos) {
        auto *deviceForm = new DeviceForm;
        qDebug("%s", qUtf8Printable("loop entered"));
        deviceHbox->addWidget(deviceForm);
        deviceForm->initWidget(a);
    }
}

