#include "headers/tabs/main/iodevicetab.h"
#include <QHBoxLayout>
#include <QTabWidget>

IODeviceTab::IODeviceTab(QTabWidget *parent)
    : QWidget(parent)
{
    setStatusTip("IO apparaten tab actief");
    //QGridLayout *grid = new QGridLayout;
    //grid->addWidget(createArduinoConfigLayout(), 0, 0);

    //this->layout()->addWidget(createArduinoConfigLayout());
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    createArduinoConfigLayout();
    createConnectedDevicesLayout();
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
}

void IODeviceTab::createConnectedDevicesLayout()
{
    //grpboxConnectedDevices = new QGroupBox("Connected devices", this);
}
