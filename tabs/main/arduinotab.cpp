#include "headers/tabs/main/arduinotab.h"
#include <QTabWidget>

ArduinoTab::ArduinoTab(QTabWidget *parent)
    : QTabWidget(parent)
{
    createLabels();
    createButtons();
    createPlainTextFields();
    initSocket();
}

void ArduinoTab::createButtons()
{
    btnPingArduino = new QPushButton("Ping arduino 1", this);
    btnPingArduino->move(30, 30);
    btnPingArduino->setMinimumWidth(150);
    connect(btnPingArduino, &QPushButton::clicked, this, &ArduinoTab::startBroadcasting);

    btnLED1 = new QPushButton("Turn on LED 1", this);
    btnLED1->move(200, 30);
    connect(btnLED1, &QPushButton::clicked, this, &ArduinoTab::btnClickLED1);

//    btnLED2 = new QPushButton("Turn on LED 2");
//    btnLED3 = new QPushButton("Turn on LED 3");
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

void ArduinoTab::initSocket()
{
    // CHANGED PORT FOR ARDUINO TEMP
    quint16 port1 = 10000;
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port1, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    connect(&timer, &QTimer::timeout, this, &ArduinoTab::broadcastDatagram);
}

void ArduinoTab::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        textEditMsg->setPlainText(datagram.constData());
        qInfo() << "Message: " << QString(datagram.constData());
        //qDebug() << "message:";
    }
}

void ArduinoTab::startBroadcasting()
{
    btnPingArduino->setDisabled(true);
    timer.start(1000);
}

void ArduinoTab::broadcastDatagram()
{
    quint16 clientPort = 9901;
    setStatusTip(tr("Broadcasting msg %1").arg(msgNr));

    QByteArray datagram = "vind arduino 1";
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, clientPort);

    msgNr++;
}

void ArduinoTab::btnClickLED1()
{
    QByteArray datagram = "";
    quint16 clientPort = 10000;

    if(isLED1_ON)
    {
        datagram = "TURN-LED1-OFF";
        btnLED1->setText("Turn on");
    }
    else
    {
        datagram = "TURN-LED1-ON";
        btnLED1->setText("Turn off");
    }
    isLED1_ON = !isLED1_ON;
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, clientPort);
}
