#include "iodevicetab.h"
#include <forms/deviceactionform.h>
#include <forms/iodeviceform.h>

IODeviceTab::IODeviceTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f),
        ioDeviceService(this)
        , hbox(new QHBoxLayout) {
    createForms();
}

void IODeviceTab::createForms() {
    devForm = new DeviceActionForm(this, Qt::Widget); // IODeviceFormFactory::createDeviceActiomForm(this);
    ioDeviceService.createDeviceActionForm(devForm);

    ioDevForm = new IODeviceForm(this, Qt::Widget);//  IODeviceFormFactory::createIODeviceForm(this);
    auto arduino = devForm->selectedArduino();
    ioDeviceService.createIODeviceForm(ioDevForm, arduino);

    if(!ioDevForm->isIODeviceListEmpty()) {
        hbox->addWidget(devForm);
        hbox->addWidget(ioDevForm);
        setLayout(hbox);

        // SIGNALS AND SLOTS
        QObject::connect(devForm, &DeviceActionForm::onSelectedArduinoChange,
                         this, &IODeviceTab::updateIODeviceTypes);
    }
}

void IODeviceTab::updateIODeviceTypes(int arduinoId) {
    ioDeviceService.updateIODeviceForm(ioDevForm, arduinoId);
}

