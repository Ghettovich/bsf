#include <QObject>
#include <QtWidgets/QHBoxLayout>
#include <incl/controller/devicecontroller.h>
#include <incl/ui/forms/deviceform.h>
#include <incl/log/bsflog.h>
#include <incl/ui/forms/deviceactionform.h>

DeviceController::DeviceController(QWidget *parent) {
    parentWidget = parent;
    arduinoRepository = new ArduinoRepository;
}

void DeviceController::createDeviceWidgets() {
    deviceHbox = new QHBoxLayout;
    arduinos = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinos) {
        auto *deviceForm = new DeviceForm(parentWidget, this);
        qDebug("%s", qUtf8Printable("loop entered"));
        deviceHbox->addWidget(deviceForm);
        deviceForm->initWidget(a);
    }
}

void DeviceController::updateArduinoDevice(const Arduino& arduino) {
    arduinoRepository->updateArduino(arduino);
}

void DeviceController::updateArduinoDevice(const Arduino& arduino, const BsfLog &log) {
    arduinoRepository->updateArduino(arduino);
    BsfLogger::addLog(log);
}

void DeviceController::createDeviceActionForm() {
    gridLayout = new QGridLayout;
    auto *deviceActionForm = new DeviceActionForm(parentWidget);
    gridLayout->addWidget(deviceActionForm, 0, 0, Qt::AlignLeft);
}
