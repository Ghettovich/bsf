#include "arduinotab.h"
#include <arduinorepo.h>
#include <forms/deviceform.h>

ArduinoTab::ArduinoTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f) {
    hbox = new QHBoxLayout(this);
    createArduinoDeviceWidgets();
}

void ArduinoTab::createArduinoDeviceWidgets() {
    ArduinoRepository arduinoRepo;
    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();

    for (Arduino a : arduinoList) {
        auto deviceForm = new DeviceForm(hbox->widget(), Qt::Widget);
        deviceForm->initWidget(a);
        hbox->addWidget(deviceForm);
    }

    setLayout(hbox);
}
