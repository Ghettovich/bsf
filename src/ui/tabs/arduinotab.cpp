#include "arduinotab.h"

ArduinoTab::ArduinoTab()
        : hbox(new QHBoxLayout) {
    ioDeviceService = new IODeviceService();
    arduinoDeviceList = ioDeviceService->createArduinoDeviceWidgetList(this);

    for(auto *f: arduinoDeviceList)
        hbox->addWidget(f);
    setLayout(hbox);
}
