#include "ui_relayform.h"
#include "relayform.h"

RelayForm::RelayForm(QWidget * parent, const IODevice& _ioDevice) :
        QWidget(parent)
        , ioDevice(_ioDevice)
        , ui(new Ui::RelayForm) {
    ui->setupUi(this);
    ioDevice = _ioDevice;
    payloadService = new PayloadService(this);

    // IDS corresponds to io devices in database which in turn matches structs defined in arduino
    setObjectName(QStringLiteral("%1").arg(ioDevice.getId()));
    createItems();
    // CONNECT EVENTS
//    connect(payloadService, &PayloadService::onReceiveIODeviceState,
//            this, &RelayForm::setIODeviceState);

//    connect(ioDevice, &IODevice::deviceStateValueChanged,
//            this, &RelayForm::setIODeviceState);
}

RelayForm::~RelayForm() {
    delete ui;
}

void RelayForm::createItems() {
    // Group Box Properties
    ui->groupBoxRelay->setTitle(ioDevice.getArduino().getName());
    // Label Properties
    ui->label->setText(ioDevice.getAction().getCode());
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

void RelayForm::setIODeviceState(int state) {
    //test setter

    if(state ==  IODevice::LOW) {
        ioDevice.setDeviceState(IODevice::LOW);
        ui->pushButtonLow->setEnabled(false);
        ui->pushButtonHigh->setEnabled(true);
    }
    else if (state == IODevice::HIGH) {
        ioDevice.setDeviceState(IODevice::HIGH);
        ui->pushButtonLow->setEnabled(true);
        ui->pushButtonHigh->setEnabled(false);
    }
    else {
        qDebug("state not recognized");
    }
}

// LOW is used to turn the relay ON
void RelayForm::onClickBtnLow() {
    QUrl ioDeviceUrl = QUrl("http://[" + ioDevice.getArduino().getIpAddress() + "]/" + ioDevice.getAction().getUrl());


    QString url = "http://[" + ioDevice.getArduino().getIpAddress() + "]/" + ioDevice.getAction().getUrl();
    qDebug("%s", qUtf8Printable(url.trimmed()));
    //payloadService->requestIODeviceState(url, ioDevice);

}

// HIGH is used to turn the relay OFF
void RelayForm::onClickBtnHigh() {
    QString url = "http://[" + ioDevice.getArduino().getIpAddress() + "]/" + ioDevice.getAction().getUrl();
    qDebug("%s", qUtf8Printable(url.trimmed()));
    //payloadService->requestIODeviceState(url, ioDevice);

}
