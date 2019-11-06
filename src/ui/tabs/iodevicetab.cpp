#include "incl/ui/tabs/iodevicetab.h"
#include <QHBoxLayout>
#include <QTabWidget>

IODeviceTab::IODeviceTab(QTabWidget *parent, QUdpSocket *udpSocket)
    : QWidget(parent),
    udpSocket(udpSocket)
{
    relayController = new RelayController;
    relayController->createTestRelayWidgets();
    setLayout(relayController->grid);
    //createArduinoConfigLayout();
    //createConnectedDevicesLayout();
    //createCensors();
}

void IODeviceTab::createArduinoConfigLayout()
{
    grpboxArduinoConfig = new QGroupBox("Arduino 1", this);
    grpboxArduinoConfig->setMinimumSize(600, 764);
    grpboxArduinoConfig->setMaximumSize(600, 1080);
    grpboxArduinoConfig->move(0, 0);

    btnRequestInfo = new QPushButton("Vraag info op.", grpboxArduinoConfig);
    btnRequestInfo->move(24, 34);
    btnRequestInfo->setMinimumSize(180, 25);
    btnRequestInfo->setMaximumSize(180, 25);
    connect(btnRequestInfo, &QPushButton::clicked, this, &IODeviceTab::btnClickedRequestInfo);

    lblIp = new QLabel("IPv4 adres:", grpboxArduinoConfig);
    lblIp->move(14, 80);
    lblIp->setMinimumSize(80, 25);
    lblIp->setMaximumSize(80, 25);

    lblPort = new QLabel("Poort:", grpboxArduinoConfig);
    lblPort->move(20, 110);
    lblPort->setMinimumSize(80, 25);
    lblPort->setMaximumSize(80, 25);

    lineEditIp = new QLineEdit(grpboxArduinoConfig);
    lineEditIp->move(100, 80);
    lineEditIp->setMinimumSize(150, 25);
    lineEditIp->setMaximumSize(200, 25);

    lineEditPort = new QLineEdit(grpboxArduinoConfig);
    lineEditPort->move(100, 110);
    lineEditPort->setMinimumSize(150, 25);
    lineEditPort->setMaximumSize(200, 25);

    textEditMsg = new QPlainTextEdit(grpboxArduinoConfig);
    textEditMsg->setPlaceholderText("Antwoord...");
    textEditMsg->setDisabled(true);
    textEditMsg->move(14, 140);
    textEditMsg->setMinimumSize(150, 100);

    // Events
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void IODeviceTab::createConnectedDevicesLayout()
{
    //grpboxConnectedDevices = new QGroupBox("Connected devices", this);
}

void IODeviceTab::createCensors()
{
    WeightCensor *sens = new WeightCensor(1, "bin-left-bottom", "sensor used get get total weight of bin.");
    qInfo() << "Message: " << QString(sens->getDeviceName());
}

void IODeviceTab::btnClickedRequestInfo()
{
    // CHANGED PORT FOR ARDUINO TEMP
    quint16 port1 = 10000;
    udpSocket->bind(port1, QUdpSocket::ShareAddress);
    broadcastDatagram("REQ_INFO", port1);
}

void IODeviceTab::broadcastDatagram(QByteArray data, quint16 port)
{
    textEditMsg->setStatusTip(tr("Broadcasting msg %1").arg(data.constData()));
    udpSocket->writeDatagram(data, QHostAddress::Broadcast, port);
}

void IODeviceTab::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        textEditMsg->setPlainText(datagram.constData());
        qInfo() << "Message: " << QString(datagram.constData());
    }
}
