#include "incl/ui/tabs/iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {
    deviceController = new DeviceController(this);
    deviceController->createDeviceActionForm();
}
