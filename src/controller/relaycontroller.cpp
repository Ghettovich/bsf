#include <QObject>
#include "incl/ui/forms/relayform.h"
#include "incl/controller/relaycontroller.h"

RelayController::RelayController(QWidget *_parent) {
    parent = _parent;
    grid = new QGridLayout;
    udpSocket = new QUdpSocket;
    ioDeviceRepository = new IODeviceRepository;
    connect(udpSocket, &QUdpSocket::readyRead, this, &RelayController::processPendingDatagrams);
}

void RelayController::createTestRelayWidgets() {
    // ONLY 1 ARDUINO FOR NOW
    int arduino_id = 1;
    ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino_id, IODeviceTypeEnum::RELAYBLOCK);

    qDebug("got arduinos...");
    for (int i = 0; i < ioDeviceList.size(); ++i) {
        auto *relayForm = new RelayForm(parent);
        relayForm->initWidget(ioDeviceList[i]);

        relayFormList.append(relayForm);

        if(i == 0) {
            qDebug("got widget...");
            grid->addWidget(relayForm, 0, 0, Qt::AlignLeft);
        }
        if(i == 1) {
            grid->addWidget(relayForm, 0, 1, Qt::AlignLeft);
        }
        if(i == 2) {
            grid->addWidget(relayForm, 0, 2, Qt::AlignLeft);
        }
        if(i == 3) {
            grid->addWidget(relayForm, 0, 3, Qt::AlignLeft);
        }
        if(i == 4) {
            grid->addWidget(relayForm, 1, 0, Qt::AlignLeft);
        }
        if(i == 5) {
            grid->addWidget(relayForm, 1, 1, Qt::AlignLeft);
        }
        if(i == 6) {
            grid->addWidget(relayForm, 1, 2, Qt::AlignLeft);
        }
        if(i == 7) {
            grid->addWidget(relayForm, 1, 3, Qt::AlignLeft);
            // TODO: remove break and create function to properly build rows and columns
            break;
        }
    }
    updateWidgetWithRelayStates();
}

void RelayController::updateWidgetWithRelayStates() {
    QString msg = "RELAY_STATE";
    QByteArray ba = msg.toLocal8Bit();

    if(!ioDeviceList.empty()) {
        udpSocket->bind(QHostAddress(ioDeviceList.first().arduino.ipAddress),
                        ioDeviceList.first().arduino.port);
        qInfo() << "writing datagram...";
        udpSocket->writeDatagram(ba, QHostAddress(ioDeviceList.first().arduino.ipAddress), ioDeviceList.first().arduino.port);
    }
    else {
        qInfo() << "arduino action list empty";
    }
}

void RelayController::processPendingDatagrams() {
    QByteArray datagram;
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


