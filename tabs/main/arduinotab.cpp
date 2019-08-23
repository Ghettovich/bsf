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
    //btnPingArduino->setMinimumHeight(80);
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
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void ArduinoTab::processPendingDatagrams()
{
    //const QString *msg;
    QByteArray datagram;
//! [2]
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        textEditMsg->setPlainText(datagram.constData());
        qInfo() << "Message: " << QString(datagram.constData());
        //qDebug() << "message:";
    }
//! [2]
}
