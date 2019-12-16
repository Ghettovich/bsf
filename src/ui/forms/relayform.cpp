#include "ui_relayform.h"
#include "incl/ui/forms/relayform.h"

RelayForm::RelayForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::RelayForm) {
    ui->setupUi(this);
    ioDevice = _ioDevice;
    payloadService = new PayloadService(this);
    // IDS corresponds to io devices in database which in turn matches structs defined in arduino
    setObjectName(QStringLiteral("%1").arg(ioDevice->getId()));
    createItems();
    setButtonState();

    connect(&NetworkRequestManagerSingleton::getInstance(), &QNetworkAccessManager::finished, this, &RelayForm::httpFinished);

    //connect(payload, &QIODevice::readyRead, this, &RelayForm::updateRelayState);
}

RelayForm::~RelayForm() {
    delete ui;
}

void RelayForm::createItems() {
    // Group Box Properties
    ui->groupBoxRelay->setTitle(ioDevice->getArduino().name);
    // Label Properties
    ui->label->setText(ioDevice->getAction().code);
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

void RelayForm::setButtonState() {
    qInfo() << QString::number(ioDevice->getDeviceState());
    qInfo() << ioDevice->getAction().url;

    if(ioDevice->getDeviceState() == IODeviceState::LOW) {
        ui->pushButtonLow->setEnabled(false);
        ui->pushButtonHigh->setEnabled(true);
    }
    else {
        ui->pushButtonLow->setEnabled(true);
        ui->pushButtonHigh->setEnabled(false);
    }
}

void RelayForm::updateRelayState() {
    if(ioDevice->getDeviceState() == 0) {
        qInfo() << "state is high";
    }
    else {

        qInfo() << "got updated iodevice from payload service";
    }

    setButtonState();
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    QString url = "http://[" + ioDevice->getArduino().ipAddress + "]/" + ioDevice->getAction().url;
    qInfo() << url;
    payloadService->requestIODeviceState(ioDevice, url);

}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    QString url = "http://[" + ioDevice->getArduino().ipAddress + "]/" + ioDevice->getAction().url;
    qInfo() << url;
    payloadService->requestIODeviceState(ioDevice, url);

}

void RelayForm::httpFinished() {
    qInfo() << "finished request (relayform)";
    updateRelayState();
}
