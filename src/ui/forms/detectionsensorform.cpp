#include "ui_detectionsensorform.h"
#include "detectionsensorform.h"

DetectionSensorForm::DetectionSensorForm(QWidget *parent, const Qt::WindowFlags  &f, DetectionSensor& _detectionSensor) :
        QWidget(parent, f)
        , detectionSensor(_detectionSensor)
        , ui(new Ui::DetectionSensorForm) {
    this->setProperty("detectionsensor-id", detectionSensor.getId());
    ui->setupUi(this);
    ui->groupBox->setTitle(detectionSensor.getIoDeviceType().getType());
    ui->labelSensorDescription->setText(detectionSensor.getDescription());
    updateDetectionSensor(detectionSensor.getDeviceState());
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

bool DetectionSensorForm::isDetectionSensorLOW() {
    return detectionSensor.getDeviceState() == IODevice::LOW;
}

void DetectionSensorForm::updateDetectionSensor(IODevice::IO_DEVICE_HIGH_LOW state) {
    if(state == IODevice::LOW) {
        detectionSensor.setDeviceState(IODevice::LOW);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else if(state == IODevice::HIGH) {
        detectionSensor.setDeviceState(IODevice::HIGH);
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : red }");
    }
    else {
        printf("\nsensor state (HIGH|LOW) not recognized");
    }
}


