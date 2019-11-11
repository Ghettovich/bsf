#include "incl/ui/forms/relayform.h"

RelayForm::RelayForm(RelayController relayController, QWidget *parent) :
        relayController(relayController),
        QWidget(parent) {
    ui.setupUi(this);
    createItems();
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress("192.168.178.23"), portListenOn);
    connect(udpSocket, &QUdpSocket::readyRead, this, &RelayForm::readDatagrams);
}

void RelayForm::createItems() {
    this->lblRelayDescription = ui.label;
    this->btnHigh = ui.pushButtonHigh;
    this->btnLow = ui.pushButtonLow;
    this->response = ui.plainTextEdit;
    // Push Button Properties
    btnHigh->setEnabled(false);
    btnLow->setEnabled(true);
    // Plain Text Set Properties
    response->setEnabled(false);
    response->setReadOnly(true);
    // Push Button Click Events
    connect(btnHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(btnLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::defaultButtonState() {
    btnHigh->setText(QStringLiteral("%1 HIGH").arg(arduinoAction.action.code));
    btnLow->setText(QStringLiteral("%1 LOW").arg(arduinoAction.action.code));
}

void RelayForm::initWidget(ArduinoAction &arduinoAction) {
    this->arduinoAction = arduinoAction;
    lblRelayDescription->setText(arduinoAction.action.description);
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

        if(QString::compare(datagram.constData(), "1") == 0) {
            btnLow->setEnabled(!btnLow->isEnabled());
            btnHigh->setEnabled(!btnHigh->isEnabled());
            response->setPlainText("Switched relay ON");
            BsfLogger::addLog("Flipped relay ON", LogSeverity::INFO);
        }
        else if(QString::compare(datagram.constData(), "0") == 0) {
            btnHigh->setEnabled(false);
            btnLow->setEnabled(true);
            response->setPlainText("Switched relay OFF");
            BsfLogger::addLog("Flipped relay OFF", LogSeverity::INFO);
        }
        else {
            response->setPlainText("message not recognized");
        }
    }
}
