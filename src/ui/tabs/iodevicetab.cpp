#include "incl/ui/tabs/iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {

    hbox = new QHBoxLayout;
    ioDeviceService = new IODeviceService(parent);
    deviceActionForm = ioDeviceService->createDeviceActionForm();

    hbox->addWidget(deviceActionForm);
    hbox->addWidget(deviceActionForm->ioDeviceForm);
    setLayout(hbox);

//    deviceController = new DeviceController(this);
//    deviceController->createDeviceActionForm();
}
