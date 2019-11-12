#include "incl/ui/tabs/iodevicetab.h"

IODeviceTab::IODeviceTab(QTabWidget *parent)
        : QWidget(parent) {
    auto *relayController = new RelayController(this);
    relayController->createTestRelayWidgets();
    setLayout(relayController->grid);

//    udpSocket = new QUdpSocket;
//    udpSocket->bind(QHostAddress("192.168.178.23"), 12300);
//    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

    //relayController.updateWidgetWithRelayStates();
}
