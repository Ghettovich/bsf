#include "ui_iodeviceform.h"
#include "incl/ui/forms/iodeviceform.h"
#include <incl/factory/iodeviceformfactory.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    arduino = _arduino;

    // DATA
    errorCodeRepository = new ErrorCodeRepository;
    ioDeviceRepository = new IODeviceRepository;
    createArduinoDeviceTypeIOComboBox();

    // LAYOUT
    grid = new QGridLayout(ui->groupBoxConnectedIO);
    grid->setContentsMargins(5, 40, 5, 5);
    // CREATE widgets with first item in Combo Box
    createIODeviceTypeFormList(ui->comboBoxIODevices->itemText(0));

    // SOCKET
    // HOST ADDRESS
    qHostAddress = new QHostAddress;
    // BROADCAST
    udpSocket = new QUdpSocket(this);
    // RECEIVE
    udpSocketListener = new QUdpSocket(this);
    udpSocketListener->bind(12300, QUdpSocket::ShareAddress);
    // SIGNALS & SLOTS
    // COMBO BOX
    connect(ui->comboBoxIODevices, SIGNAL(currentIndexChanged(
                                                  const QString&)), this, SLOT(createIODeviceTypeFormList(
                                                                                       const QString&)));
    // SOCKETS
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(onProcesPendingDatagrams()));
    connect(udpSocketListener, SIGNAL(readyRead()), this, SLOT(onIncomingDatagrams()));
}

IODeviceForm::~IODeviceForm() {
    delete ui;
}

void IODeviceForm::createArduinoDeviceTypeIOComboBox() {
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);

    if(!ioDeviceTypeList.empty()) {
        ui->comboBoxIODevices->setEnabled(true);
        qDebug("got id: %s", qUtf8Printable(QString::number(arduino->id)));
        for (auto &_ioDeviceType: ioDeviceTypeList) {
            ui->comboBoxIODevices->addItem(_ioDeviceType.type, _ioDeviceType.id);
        }
    }
    else {
        qDebug("%s", qUtf8Printable("no io device types"));
        ui->comboBoxIODevices->setEnabled(false);
    }

}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    createArduinoDeviceTypeIOComboBox();
}

void IODeviceForm::updateButtonStatesInFormList() {
    QString msg = "RELAY_STATE";
    QByteArray ba = msg.toLocal8Bit();
    qHostAddress->setAddress(arduino->ipAddress);
    udpSocket->writeDatagram(ba, *qHostAddress, arduino->port);
    qInfo() << "writing datagram...\nGot port =" << QString::number(arduino->port) << "\nWith IP ="
            << arduino->ipAddress;
}

void IODeviceForm::updateSensorStateInFormList() {
    QString msg = "SENSOR_STATE";
    QByteArray ba = msg.toLocal8Bit();
    qHostAddress->setAddress(arduino->ipAddress);
    udpSocket->writeDatagram(ba, *qHostAddress, arduino->port);
    qInfo() << "writing datagram...\nGot port =" << QString::number(arduino->port) << "\nWith IP ="
            << arduino->ipAddress;
}

void IODeviceForm::createWeightSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating weight sensor widget..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::WEIGHTSENSOR);
}

void IODeviceForm::createDetectionSensorWidgets() {
    qDebug("%s", qUtf8Printable("creating detection sensor widgets..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::DETECTIONSENSOR);
    updateSensorStateInFormList();
}

void IODeviceForm::createRelayFormWidgets() {
    qDebug("%s", qUtf8Printable("creating relay widgets..."));
    int maxColumnCount = 2;
    createIODeviceWidgets(maxColumnCount, IODeviceTypeEnum::RELAY);
    updateButtonStatesInFormList();
}

void IODeviceForm::createIODeviceWidgets(int maxColumnCount, int _ioDeviceType) {
    int column = 0, row = 0;
    ioDeviceType = ioDeviceRepository->getIODeviceType(_ioDeviceType);

    for (auto ioDevice: ioDeviceList) {
        if (column == maxColumnCount) {
            column = 0;
            row++;
        }
        ioDevice->ioDeviceType = *ioDeviceType;
        auto *ioDeviceForm = IODeviceFormFactory::getIODeviceForm(_ioDeviceType, this, ioDevice);
        ioDeviceFormList.append(ioDeviceForm);
        grid->addWidget(ioDeviceForm, row, column, Qt::AlignLeft);
        column++;
    }
    ui->groupBoxConnectedIO->setLayout(grid);
    ui->groupBoxConnectedIO->layout()->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    for(auto *form: ioDeviceFormList) {
        form->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

/* PRIVATE SLOTS */
void IODeviceForm::createIODeviceTypeFormList(const QString &deviceType) {
    killChildWidgets();
    ioDeviceList.clear();
    ioDeviceFormList.clear();

    qDebug("%s", qUtf8Printable(deviceType));

    if (QString::compare(deviceType, "weightsensor") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::WEIGHTSENSOR;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
        createWeightSensorWidgets();
    } else if (QString::compare(deviceType, "detectionsensor") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::DETECTIONSENSOR;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
        createDetectionSensorWidgets();
    } else if (QString::compare(deviceType, "relay") == 0) {
        selectedIODeviceTypeId = IODeviceTypeEnum::RELAY;
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
        createRelayFormWidgets();
    } else {
        qDebug("%s", qUtf8Printable("Could not find matching device type"));
    }
}

void IODeviceForm::onProcesPendingDatagrams() {
    QByteArray datagram;
    qInfo() << "processing datagrams on reply...";

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        QNetworkDatagram data = udpSocket->receiveDatagram();
        processNetworkDatagram(data);
    }
}

void IODeviceForm::onIncomingDatagrams() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets...";

    while (udpSocketListener->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketListener->pendingDatagramSize()));
        QNetworkDatagram data = udpSocketListener->receiveDatagram();
        processNetworkDatagram(data);
    }
}

void IODeviceForm::processNetworkDatagram(const QNetworkDatagram& datagram) {
    qInfo() << "raw data: " << datagram.data();
    QString stateMessage = "";
    QByteArray data = datagram.data();
    // 0 ok untill double digits are reached(unlikely)
    QString digits = "";
    for (int i = 0; i <datagram.data().size(); ++i) {
        QChar c = data.at(i);
        if(c.isDigit()) {
            digits.append(c);
        }
        else {
            break;
        }
    }

    int codeId = digits.toInt();

    if(datagram.data().size() > 0) {
        //QChar number = data.at(0);

            if (codeId == IODeviceTypeEnum::WEIGHTSENSOR) {
                //stateMsg = data.right(8);
            }
            if (codeId == IODeviceTypeEnum::DETECTIONSENSOR) {
                stateMessage = data.right(2).trimmed();
                qInfo() << "got new states for DETECTIONSENSOR";
            }
            if (codeId == IODeviceTypeEnum::RELAY) {
                stateMessage = data.right(8).trimmed();
                qInfo() << "got new states for RELAY";
            }
            if (codeId == ErrorCodeEnum::LIFT_STUCK) {
                setStatusTip("LIFT STUCK, MANUAL OPERATION REQUIRED");

            }

        qInfo() << "msg after trim: " << stateMessage;

        if (selectedIODeviceTypeId == codeId) {
            // setting the correct state for each widget is depended on how relayFormList is sorted
            // in the used sql statements its ordered on id, edit carefully
            for (int i = 0; i < stateMessage.length(); ++i) {
                qInfo() << "state (1 or 0) is = " << stateMessage.at(i);
                if (codeId == IODeviceTypeEnum::WEIGHTSENSOR) {

                } else if (codeId == IODeviceTypeEnum::DETECTIONSENSOR) {
                    auto f = dynamic_cast<DetectionSensorForm *>(ioDeviceFormList[i]);
                    emit f->onSensorChange(stateMessage.at(i));
                } else if (codeId == IODeviceTypeEnum::RELAY) {
                    auto f = dynamic_cast<RelayForm *>(ioDeviceFormList[i]);
                    qInfo() << "Object name =" << f->objectName();
                    emit f->setRelayButtonState(stateMessage.at(i));
                }
            }
        }
    }
    else {
        qInfo() << "got packets, but not relevant for active UI elements";
    }
}


