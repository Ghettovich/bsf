#include "iodevicetab.h"
#include <factory/iodeviceformfactory.h>

IODeviceTab::IODeviceTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f),
        ioDeviceService(this)
        , hbox(new QHBoxLayout) {
    createForms();
}

void IODeviceTab::createForms() {
    devForm = IODeviceFormFactory::createDeviceActiomForm(this);
    ioDeviceService.createDeviceActionForm(devForm);

    ioDevForm = IODeviceFormFactory::createIODeviceForm(this);
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
    qDebug("arduino changed, updateing iodevice form \nID = %s",
           qUtf8Printable(QString::number(arduinoId)));
    ioDeviceService.updateIODeviceForm(ioDevForm, arduinoId);
}

