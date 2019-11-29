#include "ui_iodeviceform.h"
#include "incl/ui/forms/iodeviceform.h"
#include <incl/factory/iodeviceformfactory.h>

IODeviceForm::IODeviceForm(QWidget *_parent, Arduino *_arduino) :
        QWidget(_parent), ui(new Ui::IODeviceForm) {
    ui->setupUi(this);
    arduino = _arduino;

    // DATA
    ioDeviceRepository = new IODeviceRepository;
    createArduinoDeviceTypeIOComboBox();

    // LAYOUT
    grid = new QGridLayout(this);
    grid->setContentsMargins(20, 65, 10, 10);
    setLayout(grid);
    qDebug("%s", qUtf8Printable("setlayout..."));

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
    qDebug("%s", qUtf8Printable("creating IODeviceType combobox with arduino id"));
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);

    qDebug("got id: %s", qUtf8Printable(QString::number(arduino->id)));
    for (auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type);
    }
}

void IODeviceForm::updateArduinoDeviceTypeIOComboBox(Arduino &_arduino) {
    ui->comboBoxIODevices->clear();
    ioDeviceTypeList.clear();
    arduino = &_arduino;
    ioDeviceTypeList = ioDeviceRepository->getArduinoIODeviceTypes(arduino->id);
    for (auto &ioDeviceType: ioDeviceTypeList) {
        ui->comboBoxIODevices->addItem(ioDeviceType.type, ioDeviceType.id);
    }
}

void IODeviceForm::updateButtonStatesInFormList() {
    QString msg = "RELAY_STATE";
    QByteArray ba = msg.toLocal8Bit();
    qHostAddress->setAddress(arduino->ipAddress);
    udpSocket->writeDatagram(ba, *qHostAddress, arduino->port);
    qInfo() << "writing datagram...\nGot port =" << QString::number(arduino->port) << "\nWith IP =" << arduino->ipAddress;
}

void IODeviceForm::updateSensorStateInFormList() {
    QString msg = "SENSOR_STATE";
    QByteArray ba = msg.toLocal8Bit();
    qHostAddress->setAddress(arduino->ipAddress);
    udpSocket->writeDatagram(ba, *qHostAddress, arduino->port);
    qInfo() << "writing datagram...\nGot port =" << QString::number(arduino->port) << "\nWith IP =" << arduino->ipAddress;
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
    qDebug("ioDevice length%s", qUtf8Printable(QString::number(ioDeviceList.length())));

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

    grid->setSizeConstraint(QLayout::SetMinimumSize);
}

void IODeviceForm::killChildWidgets() {
    QLayoutItem *child;

    while ((child = layout()->takeAt(0)) != 0) {
        //setLayout in constructor makes sure that when deleteLater is called on a child widget it will be marked for delete
        child->widget()->deleteLater();
        qDebug("%s", qUtf8Printable("child deleted"));
    }
}

/* PRIVATE SLOTS */
void IODeviceForm::createIODeviceTypeFormList(const QString &deviceType) {
    killChildWidgets();
    ioDeviceList.clear();
    ioDeviceFormList.clear();
    selectedIODeviceType = deviceType;

    qDebug("%s", qUtf8Printable(deviceType));

    if (QString::compare(deviceType, "weightsensor") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::WEIGHTSENSOR);
        createWeightSensorWidgets();
    } else if (QString::compare(deviceType, "detectionsensor") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::DETECTIONSENSOR);
        createDetectionSensorWidgets();
    } else if (QString::compare(deviceType, "relay") == 0) {
        ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino->id, IODeviceTypeEnum::RELAY);
        createRelayFormWidgets();
    } else {
        qDebug("%s", qUtf8Printable("Could not find matching device type"));
    }
}

void IODeviceForm::onProcesPendingDatagrams() {
    QByteArray datagram;
    qInfo() << "processing datagrams...";

    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString data = datagram.constData();
        qInfo() << data;
        qInfo() << "data length" << QString::number(data.length());
        qInfo() << "io device form list size" << QString::number(ioDeviceFormList.size());
        processDatagram(data);
    }
}

void IODeviceForm::onIncomingDatagrams() {
    QByteArray datagram;
    qInfo() << "got incoming udp packets...";

    while (udpSocketListener->hasPendingDatagrams()) {
        datagram.resize(int(udpSocketListener->pendingDatagramSize()));
        udpSocketListener->readDatagram(datagram.data(), datagram.size());
        qInfo() << datagram.constData();
        QString data = datagram.constData();
        processDatagram(data);
    }
}

void IODeviceForm::processDatagram(QString &data) {
    // setting the correct state for each widget is depended on how relayFormList is sorted
    // in the used sql statements its ordered on id, edit carefully
    for (int i = 0; i < data.length(); ++i) {
        if (QString::compare(selectedIODeviceType, "relay") == 0) {
            auto f = dynamic_cast<RelayForm *>(ioDeviceFormList[i]);
            qInfo() << "Object name =" << f->objectName();
            emit f->setRelayButtonState(data.at(i));
        } else if (QString::compare(selectedIODeviceType, "detectionsensor") == 0) {
            auto f = dynamic_cast<DetectionSensorForm *>(ioDeviceFormList[i]);
            emit f->onSensorChange(data.at(i));
        } else if (QString::compare(selectedIODeviceType, "weightsensor") == 0) {

        }
    }
}


