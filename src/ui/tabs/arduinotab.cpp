#include "arduinotab.h"

ArduinoTab::ArduinoTab(QTabWidget *parent)
        : QWidget(parent)
        , hbox(new QHBoxLayout) {
    ioDeviceService = new IODeviceService();
    arduinoDeviceList = ioDeviceService->createArduinoDeviceWidgetList(this);

    for(auto *f: arduinoDeviceList)
        hbox->addWidget(f);
    setLayout(hbox);
}
