#include "devicecontroller.h"
#include <repo/arduinorepo.h>
#include <repo/actionarduinorepo.h>

DeviceController::DeviceController() {
    //arduinoRepository = new ArduinoRepository;
    //actionArduinoRepository = new ActionArduinoRepository;
}

QList<DeviceForm *> DeviceController::createDeviceWidgets(QWidget *parent) {
    ArduinoRepository arduinoRepo;
    QList<DeviceForm *> widgetList;

    QList<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();
    qDebug("%s", qUtf8Printable("createDeviceWidgets called"));

    for (Arduino a : arduinoList) {
        qDebug("%s", qUtf8Printable("got arduino"));
        auto *deviceForm = new DeviceForm(parent);
        deviceForm->initWidget(a);
        widgetList.append(deviceForm);
    }

    return widgetList;
}

DeviceActionForm *DeviceController::createDeviceActionForm(QWidget *parent) {
    ArduinoRepository arduinoRepo;
    ActionArduinoRepository actionArduinORepo;
    auto deviceActionForm = new DeviceActionForm(parent);

    QList<Arduino> arduinoList = arduinoRepo.getAllActiveArduino();
    deviceActionForm->createComboBoxItems(arduinoList);
    if(!arduinoList.empty()) {
        QList<Action> arduinoActionList = actionArduinORepo.getArduinoAction(arduinoList.first().id);
        deviceActionForm->createStateActionItemList(arduinoList.first(), arduinoActionList);
    }

    return deviceActionForm;
}

IODeviceForm *DeviceController::createIODeviceForm(QWidget *parent) {
    auto ioDeviceForm = new IODeviceForm(parent);
    return ioDeviceForm;
}
