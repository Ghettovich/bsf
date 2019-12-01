#include "ui_relayform.h"
#include "incl/ui/forms/relayform.h"

RelayForm::RelayForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::RelayForm) {
    ui->setupUi(this);
    ioDevice = _ioDevice;
    setObjectName(QStringLiteral("%1").arg(ioDevice->id));
    createItems();
    udpSocket = new QUdpSocket(this);
    bcast = new QHostAddress(ioDevice->arduino.ipAddress);
    // SIGNALS & SLOTS
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

RelayForm::~RelayForm() {
    delete ui;
}

void RelayForm::createItems() {
    // Group Box Properties
    ui->groupBoxRelay->setTitle(ioDevice->arduino.name);
    // Label Properties
    ui->label->setText(ioDevice->action.code);
    // Push Button Properties
    ui->pushButtonHigh->setEnabled(false);
    ui->pushButtonLow->setEnabled(false);
    // Plain Text Set Properties
    ui->plainTextEdit->setEnabled(false);
    ui->plainTextEdit->setReadOnly(true);
    // Push Button Click Events
    connect(ui->pushButtonHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(ui->pushButtonLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::setButtonState(bool isRelayLow) {
    qInfo() << ioDevice->action.code;
    if(isRelayLow) {
        ui->pushButtonLow->setEnabled(false);
        ui->pushButtonHigh->setEnabled(true);
    }
    else {
        ui->pushButtonLow->setEnabled(true);
        ui->pushButtonHigh->setEnabled(false);
    }
}

void RelayForm::setRelayButtonState(QChar isLow) {
    if(isLow.isDigit() && isLow == '1') {
        qInfo() << "got LOW char=" << isLow;
        ui->pushButtonLow->setEnabled(false);
        ui->pushButtonHigh->setEnabled(true);
    }
    else if (isLow.isDigit() && isLow == '0') {
        qInfo() << "got HIGH char=" << isLow;
        ui->pushButtonLow->setEnabled(true);
        ui->pushButtonHigh->setEnabled(false);
    }
    else {
        qInfo() << "got:" << isLow;
    }
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    QByteArray ba = ioDevice->action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, *bcast, ioDevice->arduino.port);
}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    QByteArray ba = ioDevice->action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, *bcast, ioDevice->arduino.port);
}

void RelayForm::readDatagrams() {
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        if (QString::compare(datagram.constData(), "LOW") == 0) {
            ui->pushButtonLow->setEnabled(!ui->pushButtonLow->isEnabled());
            ui->pushButtonHigh->setEnabled(!ui->pushButtonHigh->isEnabled());
            ui->plainTextEdit->setPlainText("Switched relay ON");
            //BsfLogger::addLog("Flipped relay ON", LogSeverity::INFO);
        } else if (QString::compare(datagram.constData(), "HIGH") == 0) {
            ui->pushButtonHigh->setEnabled(false);
            ui->pushButtonLow->setEnabled(true);
            ui->plainTextEdit->setPlainText("Switched relay OFF");
            //BsfLogger::addLog("Flipped relay OFF", LogSeverity::INFO);
        } else if (QString::compare(datagram.constData(), "ERROR") == 0) {
            ui->plainTextEdit->setPlainText("received error from arduino");
        }
    }
}
