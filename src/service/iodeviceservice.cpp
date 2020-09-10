#include "service/iodeviceservice.h"

#include <repo/arduinorepo.h>
#include <repo/actionarduinorepo.h>
#include <repo/iodevicerepo.h>

IODeviceService::IODeviceService(QObject *parent, const QString& connection) : QObject(parent) {
    //deviceController = new DeviceController(this);
    if (!connection.isEmpty()) {
        defaultConnection = connection;
    } else {
        isDefaultConnection = true;
    }
}

void IODeviceService::createArduinoDeviceWidgetList(QHBoxLayout *layout) {
    ArduinoRepository arduinoRepo(defaultConnection);
    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();

    for (Arduino a : arduinoList) {
        auto deviceForm = new DeviceForm(layout->widget(), Qt::Widget);
        deviceForm->initWidget(a);
        layout->addWidget(deviceForm);
    }
}

void IODeviceService::createDeviceActionForm(DeviceActionForm * deviceActionForm) {
    ArduinoRepository arduinoRepo(defaultConnection);
    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();

    if(!arduinoList.isEmpty()) {
        int arduinoId = arduinoList.first().getId();
        deviceActionForm->createComboBoxItems(arduinoList);
        ActionArduinoRepository actionArduinORepo;
        QVector<Action> arduinoActionList = actionArduinORepo.getArduinoAction(arduinoId);
        deviceActionForm->createStateActionItemList(arduinoActionList);
    }
}

void IODeviceService::createIODeviceForm(IODeviceForm *ioDeviceForm, Arduino& arduino) {
    IODeviceRepository ioDeviceRepository;
    QVector<IODeviceType> ioDeviceTypeList;

    printf("getting io device types");
    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduino.getId());
    if(!ioDeviceTypeList.isEmpty()) {
        ioDeviceForm->onCreateArduinoDeviceTypeIOComboBox(arduino, ioDeviceTypeList);
    }
}

void IODeviceService::updateIODeviceForm(IODeviceForm *ioDeviceForm, int arduinoId) {
    ArduinoRepository arduinoRepo(defaultConnection);
    Arduino arduino = arduinoRepo.getArduino(arduinoId);

    if(arduino.getId() > 0) {
        QVector<IODeviceType> ioDeviceTypeList;
        IODeviceRepository ioDeviceRepository;
        ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduinoId);
        ioDeviceForm->onCreateArduinoDeviceTypeIOComboBox(arduino, ioDeviceTypeList);
    }
}
