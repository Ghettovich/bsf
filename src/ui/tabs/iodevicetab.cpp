#include "iodevicetab.h"

IODeviceTab::IODeviceTab() {
    hbox = new QHBoxLayout;

    ioDeviceForm = ioDeviceService.createIODeviceForm(this);
    deviceActionForm = ioDeviceService.createDeviceActionForm(this);
    ioDeviceForm->onCreateArduinoDeviceTypeIOComboBox(deviceActionForm->selectedArduinoId());

//    QObject::connect(deviceActionForm, &DeviceActionForm::arduinoIdChange,
//                ioDeviceForm, &IODeviceForm::onCreateArduinoDeviceTypeIOComboBox);

    hbox->addWidget(deviceActionForm);
    hbox->addWidget(ioDeviceForm);

    setLayout(hbox);
}

