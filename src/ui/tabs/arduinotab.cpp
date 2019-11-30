#include "incl/ui/tabs/arduinotab.h"

ArduinoTab::ArduinoTab(QTabWidget *parent)
        : QWidget(parent)
        , hbox(new QHBoxLayout) {
    ioDeviceService = new IODeviceService(this);
    arduinoDeviceList = ioDeviceService->createArduinoDeviceFormList();

    for(auto *f: arduinoDeviceList)
        hbox->addWidget(f);
    setLayout(hbox);
}
