#include <QtWidgets/QHBoxLayout>
#include <data/dbmanager.h>
#include "incl/ui/forms/devicemanager.h"
#include "incl/ui/forms/deviceform.h"

void DeviceManager::createDeviceWidgets() {
    deviceHbox = new QHBoxLayout;
    DbManager dbManager(R"(../../data/test/dbTest.db)");

    arduinos = dbManager.getAllActiveArduino();
    for(arduino a : arduinos) {
        DeviceForm *deviceForm = new DeviceForm;
        deviceHbox->addWidget(deviceForm);
        deviceForm->initWidget(a);

    }
}

