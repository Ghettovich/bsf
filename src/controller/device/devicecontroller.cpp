#include "devicecontroller.h"
#include <repo/arduinorepo.h>
#include <repo/actionarduinorepo.h>
#include <repo/iodevicerepo.h>

DeviceController::DeviceController(QObject *parent) : QObject(parent) {}

QList<DeviceForm *> DeviceController::createDeviceWidgets(QWidget *parent) {
    ArduinoRepository arduinoRepo;
    QList<DeviceForm *> widgetList;

    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinoList) {
        qDebug("%s", qUtf8Printable("got arduino"));
        auto deviceForm = new DeviceForm(parent);
        deviceForm->initWidget(a);
        widgetList.append(deviceForm);
    }

    return widgetList;
}

void DeviceController::createDeviceActionForm(DeviceActionForm *deviceActionForm) {
    ArduinoRepository arduinoRepo;
    QVector<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();

    if(!arduinoList.isEmpty()) {
        // pass a copy to
        int arduinoId = arduinoList.first().getId();
        qDebug("first id in list is = %s", qUtf8Printable(QString::number(arduinoId)));

        deviceActionForm->createComboBoxItems(arduinoList);
        ActionArduinoRepository actionArduinORepo;
        QVector<Action> arduinoActionList = actionArduinORepo.getArduinoAction(arduinoId);
        deviceActionForm->createStateActionItemList(arduinoActionList);
    }
}

void DeviceController::createIODeviceForm(IODeviceForm *ioDeviceForm, Arduino& arduino) {
    IODeviceRepository ioDeviceRepository;
    QVector<IODeviceType> ioDeviceTypeList = QVector<IODeviceType>();

    qDebug("getting io device types");
    ioDeviceTypeList = ioDeviceRepository.getArduinoIODeviceTypes(arduino.getId());
    if(!ioDeviceTypeList.isEmpty()) {
        ioDeviceForm->onCreateArduinoDeviceTypeIOComboBox(arduino, ioDeviceTypeList);
    }
}
