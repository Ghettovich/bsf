#include "ui_detectionsensorform.h"
#include "detectionsensorform.h"

DetectionSensorForm::DetectionSensorForm(QWidget *parent, const Qt::WindowFlags  &f, DetectionSensor& _detectionSensor) :
        QWidget(parent, f)
        , detectionSensor(_detectionSensor)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    ui->labelStatus->setText("STATUS");
    ui->groupBox->setTitle(detectionSensor.getIoDeviceType().getType());
    ui->labelSensorDescription->setText(detectionSensor.getDescription());
    setDetectionSensorState(detectionSensor.getDeviceState());

    //connect(ioDevice, &IODevice::deviceStateValueChanged, this, &DetectionSensorForm::setDetectionSensorState);
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

bool DetectionSensorForm::getDeviceState() {
    if(detectionSensor.getDeviceState() == IODevice::LOW) {
        return true;
    }
    else if(detectionSensor.getDeviceState() == IODevice::HIGH) {
        return false;
    }
    return false;
}

void DetectionSensorForm::setDetectionSensorState(IODevice::IO_DEVICE_HIGH_LOW state) {
    if(state == IODevice::LOW) {
        qDebug("sensor is low (ON)");
        detectionSensor.setDeviceState(IODevice::LOW);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else if(state == IODevice::HIGH) {
        qDebug("sensor is high (OFF)");
        detectionSensor.setDeviceState(IODevice::HIGH);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : red }");
    }
    else {
        qDebug("sensor state (HIGH|LOW) not recognized");
    }
}


