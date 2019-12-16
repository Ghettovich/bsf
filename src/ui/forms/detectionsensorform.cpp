#include "ui_detectionsensorform.h"
#include <incl/ui/forms/detectionsensorform.h>

DetectionSensorForm::DetectionSensorForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    qDebug("%s", qUtf8Printable("called constructor detection sensor widget..."));
    ioDevice = _ioDevice;
    ui->labelStatus->setText("STATUS");
    ui->groupBox->setTitle(ioDevice->getIoDeviceType().type);
    ui->labelSensorDescription->setText(ioDevice->getDescription());

    connect(ioDevice, &IODevice::deviceStateValueChanged, this, &DetectionSensorForm::setIODeviceState);
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

void DetectionSensorForm::setIODeviceState(IODeviceState state) {
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
