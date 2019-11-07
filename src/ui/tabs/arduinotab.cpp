#include "incl/ui/tabs/arduinotab.h"
#include <QTabWidget>
#include <QSqlRecord>
#include <incl/ui/forms/deviceform.h>

ArduinoTab::ArduinoTab(QTabWidget *parent)
        : QWidget(parent) {
    DeviceController deviceManager;
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
