#include <QTabWidget>
#include "incl/ui/tabs/arduinotab.h"
#include "incl/controller/devicecontroller.h"

ArduinoTab::ArduinoTab(QTabWidget *parent)
        : QWidget(parent) {
    auto *deviceController = new DeviceController(this);
    deviceController->createDeviceWidgets();
}
