#include "iodevicetab.h"


IODeviceTab::IODeviceTab(QWidget * parent) :
ioDeviceService(this)
        , hbox(new QHBoxLayout) {
    devForm = new DeviceActionForm(this);
    ioDeviceService.createDeviceActionForm(devForm);

    ioDevForm = new IODeviceForm(this);
    auto arduino = devForm->selectedArduino();
    ioDeviceService.createIODeviceForm(ioDevForm, arduino);

    hbox->addWidget(devForm);
    hbox->addWidget(ioDevForm);
    setLayout(hbox);

    // SIGNALS AND SLOTS
    QObject::connect(devForm, &DeviceActionForm::onSelectedArduinoChange,
            this, &IODeviceTab::updateIODeviceTypes);

}

void IODeviceTab::updateIODeviceTypes(int arduinoId) {
    qDebug("arduino changed, updateing iodevice form \nID = %s",
            qUtf8Printable(QString::number(arduinoId)));
    ioDeviceService.updateIODeviceForm(ioDevForm, arduinoId);
}

