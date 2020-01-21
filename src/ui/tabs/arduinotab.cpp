#include "arduinotab.h"

ArduinoTab::ArduinoTab(QWidget *parent) : QWidget(parent) {
    hbox = new QHBoxLayout(this);
    ioDeviceService = new IODeviceService(this);
    ioDeviceService->createArduinoDeviceWidgetList(hbox);
    setLayout(hbox);
}
