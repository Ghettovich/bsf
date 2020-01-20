#include "ui_detectionsensorform.h"
#include "detectionsensorform.h"

DetectionSensorForm::DetectionSensorForm(QWidget *parent, const IODevice& _ioDevice) :
        QWidget(parent)
        , ioDevice(_ioDevice)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    qDebug("%s", qUtf8Printable("called constructor detection sensor widget..."));
    ioDevice = _ioDevice;
    ui->labelStatus->setText("STATUS");
    ui->groupBox->setTitle(ioDevice.getIoDeviceType().getType());
    ui->labelSensorDescription->setText(ioDevice.getDescription());
    setDetectionSensorState(ioDevice.getDeviceState());

    //connect(ioDevice, &IODevice::deviceStateValueChanged, this, &DetectionSensorForm::setDetectionSensorState);
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

bool DetectionSensorForm::getDeviceState() {
    if(ioDevice.getDeviceState() == IODevice::LOW) {
        return true;
    }
    else if(ioDevice.getDeviceState() == IODevice::HIGH) {
        return false;
    }
    return false;
}

void DetectionSensorForm::setDetectionSensorState(int state) {
    if(state == IODevice::LOW) {
        qDebug("sensor is low (ON)");
        ioDevice.setDeviceState(IODevice::LOW);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else if(state == IODevice::HIGH) {
        qDebug("sensor is high (OFF)");
        ioDevice.setDeviceState(IODevice::HIGH);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : red }");
    }
    else {
        qDebug("sensor state (HIGH|LOW) not recognized");
    }
}


