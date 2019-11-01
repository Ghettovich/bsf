#include "headers/tabs/main/arduinotab.h"
#include <QTabWidget>
#include <forms/deviceform.h>

ArduinoTab::ArduinoTab(QTabWidget *parent)
    : QWidget(parent)
{
    //DeviceForm *deviceWidget = new DeviceForm(this);
    //deviceWidget->show();
    //QGridLayout *grid = new QGridLayout(this);
    QHBoxLayout *deviceHbox = new QHBoxLayout;

    for (int i = 0; i < 2; ++i) {
        DeviceForm *deviceForm = new DeviceForm;

        //deviceForm->setMinimumSize(484, 837);
        deviceHbox->addWidget(deviceForm);
        qInfo() << "deviceForm min. height: " << deviceForm->minimumHeight();
    }

    qInfo() << "parent min. height: " << parentWidget()->minimumHeight();
    qInfo() << "parent min. width: " << parentWidget()->minimumWidth();
    setLayout(deviceHbox);


//    createLabels();
//    createButtons();
//    createPlainTextFields();
}

void ArduinoTab::createButtons()
{
    btnPingArduino = new QPushButton("Ping arduino 1", this);
    btnPingArduino->move(30, 30);
    btnPingArduino->setMinimumWidth(150);
    //connect(btnPingArduino, &QPushButton::clicked, this, &ArduinoTab::startBroadcasting);

    btnLED1 = new QPushButton("Turn on LED 1", this);
    btnLED1->move(200, 30);
    connect(btnLED1, &QPushButton::clicked, this, &ArduinoTab::btnClickLED1);
}

void ArduinoTab::createLabels()
{
    lblPingDevice = new QLabel(this);
    lblPingDevice->move(30, 70);
    lblPingDevice->setText("Response: ...");
}

void ArduinoTab::createPlainTextFields()
{
    textEditMsg = new QPlainTextEdit(this);
    textEditMsg->setPlaceholderText("Antwoord...");
    textEditMsg->setDisabled(true);
    textEditMsg->move(30, 100);
    textEditMsg->setMinimumSize(150, 100);
}

void ArduinoTab::btnClickLED1()
{
    quint16 clientPort = 10000;

    if(isLED1_ON)
    {
        //udpServer->broadcastDatagram(clientPort, "TURN-LED1-OFF");
        btnLED1->setText("Turn on");
    }
    else
    {
        //udpServer->broadcastDatagram(clientPort, "TURN-LED1-ON");
        btnLED1->setText("Turn off LED 1");
    }
    isLED1_ON = !isLED1_ON;
    //textEditMsg->setPlainText(udpServer->getResponseMsg());
}
