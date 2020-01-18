#include "ui_detectionsensorform.h"
#include "detectionsensorform.h"

DetectionSensorForm::DetectionSensorForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    qDebug("%s", qUtf8Printable("called constructor detection sensor widget..."));
    ioDevice = _ioDevice;
    ui->labelStatus->setText("STATUS");
    ui->groupBox->setTitle(ioDevice->getIoDeviceType().type);
    ui->labelSensorDescription->setText(ioDevice->getDescription());
    setIODeviceState(ioDevice->getDeviceState());

    connect(ioDevice, &IODevice::deviceStateValueChanged, this, &DetectionSensorForm::setIODeviceState);
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

bool DetectionSensorForm::getDeviceState() {
    if(ioDevice->getDeviceState() == IODeviceState::LOW) {
        return true;
    }
    else if(ioDevice->getDeviceState() == IODeviceState::HIGH) {
        return false;
    }
    return false;
}

void DetectionSensorForm::setIODeviceState(IODeviceState state) {
    //should return proper val now
    ioDevice->setDeviceState(state);
    if(state == IODeviceState::LOW) {
        qDebug("sensor is low (ON)");
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else if(state == IODeviceState::HIGH) {
        qDebug("sensor is high (OFF)");
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : red }");
    }
    else {
        qDebug("not recognized");
    }
}
