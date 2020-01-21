#include "iodevicetab.h"
#include <ui/forms/deviceactionform.h>
#include <ui/forms/iodeviceform.h>

IODeviceTab::IODeviceTab(QWidget * parent) :
ioDeviceService(this)
        , hbox(new QHBoxLayout) {
    auto *devForm = new DeviceActionForm(this);
    ioDeviceService.createDeviceActionForm(devForm);

    auto *ioDevForm = new IODeviceForm(this);
    auto arduino = devForm->selectedArduino();
    ioDeviceService.createIODeviceForm(ioDevForm, arduino);

    hbox->addWidget(devForm);
    hbox->addWidget(ioDevForm);
    setLayout(hbox);
}

