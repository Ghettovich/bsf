#include "iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {

    hbox = new QHBoxLayout;
    //ioDeviceService = new IODeviceService();

    hbox->addWidget(ioDeviceService.createDeviceActionForm(this));
    hbox->addWidget(ioDeviceService.createIODeviceForm(this));
    //hbox->addWidget(deviceActionForm->ioDeviceForm);
    setLayout(hbox);
//
//    deviceController = new DeviceController(this);
//    deviceController->createDeviceActionForm();
}
