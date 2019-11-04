#include "incl/ui/tabs/arduinotab.h"
#include <QTabWidget>
#include <QSqlRecord>
#include <incl/ui/forms/deviceform.h>
#include <incl/ui/forms/devicemanager.h>

//static const QString path = ("../test/database/dbTest.db");

ArduinoTab::ArduinoTab(QTabWidget *parent)
        : QWidget(parent) {
    //DbManager dbManager(path);
    //auto bla = dbManager.getAllActiveArduino();
    DeviceManager deviceManager;
    deviceManager.createDeviceWidgets();
    setLayout(deviceManager.deviceHbox);
}

void ArduinoTab::btnClickLED1() {
    //quint16 clientPort = 10000;

//    if (isLED1_ON) {
//        //udpServer->broadcastDatagram(clientPort, "TURN-LED1-OFF");
//        btnLED1->setText("Turn on");
//    } else {
//        //udpServer->broadcastDatagram(clientPort, "TURN-LED1-ON");
//        btnLED1->setText("Turn off LED 1");
//    }
//    isLED1_ON = !isLED1_ON;
    //textEditMsg->setPlainText(udpServer->getResponseMsg());
}
