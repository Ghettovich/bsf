#include "headers/tabs/main/arduinotab.h"
#include <QTabWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <forms/deviceform.h>
#include <data/dbmanager.h>

ArduinoTab::ArduinoTab(QTabWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *deviceHbox = new QHBoxLayout;
    DbManager dbManager(R"(../../data/test/dbTest.db)");
    QList<ArduinoDevice *> arduinos = dbManager.getAllActiveArduino();
    for(ArduinoDevice *& a : arduinos) {
        DeviceForm *deviceForm = new DeviceForm;
        deviceHbox->addWidget(deviceForm);
        deviceForm->groupBoxArduino->setTitle(a->getName());
        deviceForm->lineEditName->setText(a->getName());
        deviceForm->lineEditIpAddress->setText(a->getIpAddress());
        deviceForm->lineEditNPort->setText(QStringLiteral("%1").arg(a->getPort()));
        deviceForm->plainTextEditDescription->setPlainText(a->getDescription());
        //qDebug() << a->getName() << " " << a->getDescription();
    }

    setLayout(deviceHbox);
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
    //quint16 clientPort = 10000;

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
