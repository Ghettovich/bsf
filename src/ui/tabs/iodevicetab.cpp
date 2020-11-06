#include "iodevicetab.h"
#include <forms/deviceactionform.h>
#include <forms/iodeviceform.h>
#include <arduinorepo.h>
#include <iodevicerepo.h>

IODeviceTab::IODeviceTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f)
        , hbox(new QHBoxLayout) {
    createDeviceActionForm();
    createIODeviceForm();
}

void IODeviceTab::createDeviceActionForm() {
    devForm = new DeviceActionForm(this, Qt::Widget);

    ArduinoRepository arduinoRepo;
    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();

    if(!arduinoList.isEmpty()) {
        int arduinoId = arduinoList.first().getId();
        devForm->createComboBoxItems(arduinoList);
        ActionArduinoRepository actionArduinORepo;
        QVector<Action> arduinoActionList = actionArduinORepo.getArduinoAction(arduinoId);
        devForm->createStateActionItemList(arduinoActionList);
    }
}

void IODeviceTab::createIODeviceForm() {
    ioDevForm = new IODeviceForm(this, Qt::Widget);
    auto arduino = devForm->selectedArduino();

    IODeviceRepository ioDeviceRepository;
    QVector<IODeviceType> ioDeviceTypeList;

    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduino.getId());
    if(!ioDeviceTypeList.isEmpty()) {
        ioDevForm->onCreateArduinoDeviceTypeIOComboBox(arduino, ioDeviceTypeList);

        hbox->addWidget(devForm);
        hbox->addWidget(ioDevForm);
        setLayout(hbox);

        // SIGNALS AND SLOTS
        QObject::connect(devForm, &DeviceActionForm::onSelectedArduinoChange,
                         this, &IODeviceTab::updateIODeviceTypes);
    }
}

void IODeviceTab::updateIODeviceTypes(int arduinoId) {
    ArduinoRepository arduinoRepo;
    Arduino arduino = arduinoRepo.getArduino(arduinoId);

    if(arduino.getId() > 0) {
        QVector<IODeviceType> ioDeviceTypeList;
        IODeviceRepository ioDeviceRepository;
        ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);
        ioDevForm->onCreateArduinoDeviceTypeIOComboBox(arduino, ioDeviceTypeList);
    }
}

