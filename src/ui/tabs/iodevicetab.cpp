#include "iodevicetab.h"

IODeviceTab::IODeviceTab(QWidget * parent) :
ioDeviceService(this)
        , hbox(new QHBoxLayout) {
    auto *devForm = new DeviceActionForm(this);
    ioDeviceService.createDeviceActionForm(devForm);

    auto *ioDevForm = new IODeviceForm(this);
    ioDeviceService.createIODeviceForm(ioDevForm, devForm->selectedArduinoId());


//    QObject::connect(deviceActionForm, &DeviceActionForm::arduinoIdChange,
//                ioDeviceForm, &IODeviceForm::onCreateArduinoDeviceTypeIOComboBox);

    hbox->addWidget(devForm);
    hbox->addWidget(ioDevForm);
    setLayout(hbox);
}

