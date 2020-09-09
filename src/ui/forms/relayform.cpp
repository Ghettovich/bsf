#include "ui_relayform.h"
#include "relayform.h"

RelayForm::RelayForm(QWidget *parent, const Qt::WindowFlags &f, Relay &_relay) :
        QWidget(parent, f), relay(_relay), ui(new Ui::RelayForm) {
    ui->setupUi(this);

    this->setProperty("relay-id", QVariant(_relay.getId()));
    createItems();

    QUrl fullStateURL = QUrl("http://[" + relay.getArduino()->getIpAddress() + "]/");
}

RelayForm::~RelayForm() {
    delete ui;
}

void RelayForm::createItems() {
    // Group Box Properties
    ui->groupBoxRelay->setTitle(relay.getIoDeviceType().getType());
    // Label Properties
    ui->labelIODeviceDesc->setText(relay.getDescription());
    // Push Button Properties
    ui->pushButtonHigh->setEnabled(false);
    ui->pushButtonLow->setEnabled(false);
    // Push Button Click Events
    QObject::connect(ui->pushButtonHigh, &QPushButton::clicked, this, &RelayForm::onClickBtnHigh);
    connect(ui->pushButtonLow, &QPushButton::clicked, this, &RelayForm::onClickBtnLow);
}

void RelayForm::setIODeviceState(IODevice::IO_DEVICE_HIGH_LOW state) {
    //test setter
    if (state == IODevice::LOW) {
        relay.setDeviceState(IODevice::LOW);
        ui->pushButtonLow->setEnabled(false);
        ui->pushButtonHigh->setEnabled(true);
    } else if (state == IODevice::HIGH) {
        relay.setDeviceState(IODevice::HIGH);
        ui->pushButtonLow->setEnabled(true);
        ui->pushButtonHigh->setEnabled(false);
    } else {
        printf("\nState not recognized");
    }
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    requestState();
}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    requestState();
}

void RelayForm::requestState() {
    QUrl ioDeviceUrl = QUrl("http://[" + relay.getArduino()->getIpAddress() + "]/relay/" + QString("%1").arg(relay.getId()));
    emit sendRequest(ioDeviceUrl);
}
