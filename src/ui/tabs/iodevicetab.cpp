#include "incl/ui/tabs/iodevicetab.h"
#include <QHBoxLayout>
#include <QTabWidget>

IODeviceTab::IODeviceTab(QTabWidget *parent, QUdpSocket *udpSocket)
    : QWidget(parent),
    udpSocket(udpSocket)
{
    RelayController relayController;
    relayController.createTestRelayWidgets();
    setLayout(relayController.grid);
}

void IODeviceTab::btnClickedRequestInfo()
{
    // CHANGED PORT FOR ARDUINO TEMP
    quint16 port1 = 10000;
    udpSocket->bind(port1, QUdpSocket::ShareAddress);
    broadcastDatagram("REQ_INFO", port1);
}

void IODeviceTab::broadcastDatagram(const QByteArray &data, quint16 port)
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
