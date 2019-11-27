#include <incl/ui/forms/relayform.h>
#include <incl/controller/relaycontroller.h>

RelayController::RelayController(QWidget *_parent) {
    parent = _parent;
    grid = new QGridLayout;
    ioDeviceRepository = new IODeviceRepository;
    arduinoRepository = new ArduinoRepository;
    //TODO: create for multiple arduino's
    int arduino_id = 1;
    arduino = arduinoRepository->getArduino(arduino_id);
    // SOCKET
    bcast = new QHostAddress;//(arduino.ipAddress);
    // BROADCAST
    udpSocket = new QUdpSocket(this);
    // RECEIVE
    udpSocketListener = new QUdpSocket(this);
    udpSocketListener->bind(12300, QUdpSocket::ShareAddress);

    // HOST ADDRESS

    // SIGNAL & SLOT
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    connect(udpSocketListener, SIGNAL(readyRead()),this, SLOT(onListenUDPackets()));
}

void RelayController::createTestRelayWidgets() {
    // ONLY 1 ARDUINO FOR NOW
    int arduino_id = 1, row = 0, col = 0, columnBreak = 4;
    ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino_id, IODeviceTypeEnum::RELAY);

    for (int i = 0; i < ioDeviceList.size(); ++i) {
        auto *relayForm = new RelayForm(parent, &ioDeviceList[i]);
        relayFormList.append(relayForm);

        if (i == columnBreak) {
            col = 0;
            row++;
        }
        grid->addWidget(relayForm, row, col, Qt::AlignLeft);
        col++;
    }
}

void RelayController::updateWidgetWithRelayStates() {
    QString msg = "RELAY_STATE";
    QByteArray ba = msg.toLocal8Bit();
    bcast->setAddress(arduino.ipAddress);
    udpSocket->writeDatagram(ba, *bcast, arduino.port);
    qInfo() << "writing datagram...\nGot port = " << QString::number(arduino.port);
}

/* PRIVATE SIGNALS */
void RelayController::processPendingDatagrams() {
    QByteArray datagram;
    qInfo() << "processing datagrams...";
    while (udpSocket->hasPendingDatagrams()) {

        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        QString data = datagram.constData();
        qInfo() << data;
        // setting the correct state for each widget is depended on how relayFormList is sorted
        // in the used sql statements its ordered on id, edit carefully
        for (int i = 0; i < data.length(); ++i) {
            relayFormList[i]->setButtonState(data.at(i) == '1');
        }
    }
}


void RelayController::onListenUDPackets() {
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        qInfo() << datagram.constData();
    }
}
