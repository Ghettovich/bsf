#include "arduinotab.h"

ArduinoTab::ArduinoTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f) {
    hbox = new QHBoxLayout(this);
    ioDeviceService = new IODeviceService(this);
    ioDeviceService->createArduinoDeviceWidgetList(hbox);
    setLayout(hbox);
}
