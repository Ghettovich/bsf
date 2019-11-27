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
//    destPort = _ioDevice->arduino.port;

    connect(udpSocket, &QUdpSocket::readyRead, this, &RelayForm::readDatagrams);
}

RelayForm::~RelayForm() {
    delete ui;
}

void RelayForm::createItems() {
    this->groupBox = ui->groupBoxRelay;
    this->lblRelayDescription = ui->label;
    this->btnHigh = ui->pushButtonHigh;
    this->btnLow = ui->pushButtonLow;
    this->response = ui->plainTextEdit;
    // Group Box Properties
    groupBox->setTitle(ioDevice->arduino.name);
    // Label Properties
    lblRelayDescription->setText(ioDevice->action.code);
    // Push Button Properties
    btnHigh->setEnabled(false);
    btnLow->setEnabled(false);
    btnHigh->setText("HIGH");
    btnLow->setText("LOW");
    // Plain Text Set Properties
    response->setEnabled(false);
    response->setReadOnly(true);
    // Push Button Click Events
    connect(btnHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(btnLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::setButtonState(bool isRelayLow) {
    qInfo() << ioDevice->action.code;
    if(isRelayLow) {
        btnLow->setEnabled(false);
        btnHigh->setEnabled(true);
    }
    else {
        btnLow->setEnabled(true);
        btnHigh->setEnabled(false);
    }
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    qInfo() << "on click low ";
    qInfo() << "port=" << QString::number(ioDevice->arduino.port);
    QByteArray ba = ioDevice->action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, *bcast, ioDevice->arduino.port);
}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    qInfo() << "on click high ";
    qInfo() << "port=" << QString::number(ioDevice->arduino.port);
    QByteArray ba = ioDevice->action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, *bcast, ioDevice->arduino.port);
}

void RelayForm::readDatagrams() {
    qInfo() << "sending: " << ioDevice->action.code;
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        if (QString::compare(datagram.constData(), "LOW") == 0) {
            btnLow->setEnabled(!btnLow->isEnabled());
            btnHigh->setEnabled(!btnHigh->isEnabled());
            response->setPlainText("Switched relay ON");
            //BsfLogger::addLog("Flipped relay ON", LogSeverity::INFO);
        } else if (QString::compare(datagram.constData(), "HIGH") == 0) {
            btnHigh->setEnabled(false);
            btnLow->setEnabled(true);
            response->setPlainText("Switched relay OFF");
            //BsfLogger::addLog("Flipped relay OFF", LogSeverity::INFO);
        } else if (QString::compare(datagram.constData(), "ERROR") == 0) {
            response->setPlainText("received error from arduino");
        } else {
            response->setPlainText("message not recognized");
        }
    }
}
