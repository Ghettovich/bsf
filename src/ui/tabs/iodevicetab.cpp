#include "iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {
    hbox = new QHBoxLayout;

    ioDeviceForm = ioDeviceService.createIODeviceForm(this);
    deviceActionForm = ioDeviceService.createDeviceActionForm(this);
    ioDeviceForm->onCreateArduinoDeviceTypeIOComboBox(deviceActionForm->selectedArduinoId());

    emit deviceActionForm->arduinoIdChange(deviceActionForm->selectedArduinoId());

    hbox->addWidget(deviceActionForm);
    hbox->addWidget(ioDeviceForm);

    setLayout(hbox);
}
