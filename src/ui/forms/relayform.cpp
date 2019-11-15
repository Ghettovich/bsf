#include <incl/ui/forms/relayform.h>
#include "ui_relayform.h"

RelayForm::RelayForm(QWidget *parent) :
        QWidget(parent), ui(new Ui::RelayForm) {
    ui->setupUi(this);
    createItems();
    udpSocket = new QUdpSocket(this);
    //udpSocket->bind(QHostAddress(arduinoAction.arduinoDev.ipAddress), portListenOn);
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
    groupBox->setTitle(arduinoAction.arduinoDev.name);
    // Push Button Properties
    btnHigh->setEnabled(false);
    btnLow->setEnabled(false);
    // Plain Text Set Properties
    response->setEnabled(false);
    response->setReadOnly(true);
    // Push Button Click Events
    connect(btnHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(btnLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::defaultButtonState() {
    btnHigh->setText("HIGH");
    btnLow->setText("LOW");
}

void RelayForm::setButtonState(bool isRelayLow) {
    qInfo() << arduinoAction.action.code;
    if(isRelayLow) {
        btnLow->setEnabled(false);
        btnHigh->setEnabled(true);
    }
    else {
        btnLow->setEnabled(true);
        btnHigh->setEnabled(false);
    }
}

void RelayForm::initWidget(const ArduinoAction &_arduinoAction) {
    arduinoAction = _arduinoAction;
    setObjectName(QStringLiteral("%1").arg(arduinoAction.id));
    lblRelayDescription->setText(_arduinoAction.action.code);
    defaultButtonState();
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    QByteArray ba = arduinoAction.action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, QHostAddress(arduinoAction.arduinoDev.ipAddress), arduinoAction.arduinoDev.port);
}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    QByteArray ba = arduinoAction.action.code.toLocal8Bit();
    udpSocket->writeDatagram(ba, QHostAddress(arduinoAction.arduinoDev.ipAddress), arduinoAction.arduinoDev.port);
}

void RelayForm::readDatagrams() {
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());

        if (QString::compare(datagram.constData(), "1") == 0) {
            btnLow->setEnabled(!btnLow->isEnabled());
            btnHigh->setEnabled(!btnHigh->isEnabled());
            response->setPlainText("Switched relay ON");
            //BsfLogger::addLog("Flipped relay ON", LogSeverity::INFO);
        } else if (QString::compare(datagram.constData(), "0") == 0) {
            btnHigh->setEnabled(false);
            btnLow->setEnabled(true);
            response->setPlainText("Switched relay OFF");
            //BsfLogger::addLog("Flipped relay OFF", LogSeverity::INFO);
        } else {
            response->setPlainText("message not recognized");
        }
    }
}
