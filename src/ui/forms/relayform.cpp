#include "incl/ui/forms/relayform.h"

RelayForm::RelayForm(RelayController relayController, QWidget *parent) :
        relayController(relayController),
        QWidget(parent) {
    ui.setupUi(this);
    createItems();
    udpServer = new Server;
}

void RelayForm::createItems() {
    this->lblRelayDescription = ui.label;
    this->btnHigh = ui.pushButtonHigh;
    this->btnLow = ui.pushButtonLow;
    this->response = ui.plainTextEdit;
    // Plain Text Set Properties
    response->setEnabled(false);
    response->setReadOnly(true);
    // Push Button Click Events
    connect(btnHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(btnLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::defaultButtonState() {
    btnHigh->setEnabled(false);
    btnHigh->setText(QStringLiteral("%1 HIGH").arg(arduinoAction.action.code));
    btnLow->setEnabled(true);
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
    udpServer->broadcastDatagram(arduinoAction.arduinoDev.port, ba.constData());

    if(udpServer->getResponseMsg() == "1") {
        btnLow->setEnabled(!btnLow->isEnabled());
        btnHigh->setEnabled(!btnHigh->isEnabled());
        response->setPlainText("Switched relay ON");
    }
    else {
        response->setPlainText(QStringLiteral("Failed to switch relay ON\n%1").arg(udpServer->getResponseMsg()));
    }
}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    QByteArray ba = arduinoAction.action.code.toLocal8Bit();
    udpServer->broadcastDatagram(arduinoAction.arduinoDev.port, ba.constData());

    if(udpServer->getResponseMsg() == "0") {
        btnHigh->setEnabled(!btnHigh->isEnabled());
        btnLow->setEnabled(!btnLow->isEnabled());
        response->setPlainText("Switched relay OFF");
    }
    else {
        response->setPlainText(QStringLiteral("Failed to switch relay ON\n%1").arg(udpServer->getResponseMsg()));
    }
}
