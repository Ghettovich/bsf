#include "incl/controller/devicecontroller.h"
#include <QObject>

#include <incl/log/bsflog.h>


DeviceController::DeviceController(QWidget *parent) {
    parentWidget = parent;
    arduinoRepository = new ArduinoRepository;
}

QList<DeviceForm *> DeviceController::createDeviceWidgets() {
    QList<DeviceForm *> widgetList;
    //deviceHbox = new QHBoxLayout(parentWidget);
    arduinos = arduinoRepository->getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinos) {
        auto *deviceForm = new DeviceForm(parentWidget);
        deviceForm->initWidget(a);
        widgetList.append(deviceForm);
    }

    return widgetList;

//    for (Arduino a : arduinos) {
//        auto *deviceForm = new DeviceForm(parentWidget, this);
//        qDebug("%s", qUtf8Printable("loop entered"));
//        deviceHbox->addWidget(deviceForm, 0, Qt::AlignLeft);
//        deviceForm->initWidget(a);
//    }
}

DeviceActionForm *DeviceController::createDeviceActionForm() {
    //deviceHbox = new QHBoxLayout(parentWidget);
    auto *deviceActionForm = new DeviceActionForm(parentWidget);
    return deviceActionForm;
    //deviceHbox->addWidget(deviceActionForm, 0, Qt::AlignLeft);
    //deviceHbox->addWidget(deviceActionForm->ioDeviceForm, 2, Qt::AlignLeft);
}

