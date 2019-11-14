#include "incl/ui/tabs/iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {
    deviceActionForm = new DeviceActionForm(this);
}
