#include <QtWidgets/QHBoxLayout>
#include <data/dbmanager.h>
#include "incl/ui/forms/devicemanager.h"
#include "incl/ui/forms/deviceform.h"

void DeviceManager::createDeviceWidgets(QWidget *parent) {

    deviceHbox = new QHBoxLayout;

    DbManager dbManager(R"(../../data/test/dbTest.db)");

    arduinoDevices = dbManager.getAllActiveArduino();
    for(ArduinoDevice *& a : arduinoDevices) {
        DeviceForm *deviceForm = new DeviceForm;
        deviceHbox->addWidget(deviceForm);
        deviceForm->groupBoxArduino->setTitle(a->getName());
        deviceForm->lineEditName->setText(a->getName());
        deviceForm->lineEditIpAddress->setText(a->getIpAddress());
        deviceForm->lineEditNPort->setText(QStringLiteral("%1").arg(a->getPort()));
        deviceForm->plainTextEditDescription->setPlainText(a->getDescription());
        //qDebug() << a->getName() << " " << a->getDescription();
    }

}

void DeviceManager::addNewDeviceWdiget(QWidget *parent) {

}
