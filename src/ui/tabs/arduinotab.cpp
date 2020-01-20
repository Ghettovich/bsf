#include "arduinotab.h"

ArduinoTab::ArduinoTab(QWidget *parent) :
        QWidget(parent)
        , hbox(new QHBoxLayout) {
    ioDeviceService = new IODeviceService(this);
    arduinoDeviceList = ioDeviceService->createArduinoDeviceWidgetList(this);

    for (auto arduinoDevice: arduinoDeviceList)
        hbox->addWidget(arduinoDevice);
    setLayout(hbox);
}
