#include "ui_detectionsensorform.h"
#include <incl/ui/forms/detectionsensorform.h>

DetectionSensorForm::DetectionSensorForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    qDebug("%s", qUtf8Printable("called constructor detection sensor widget..."));
    ioDevice = _ioDevice;
    ui->labelStatus->setText("STATUS");
    ui->groupBox->setTitle(ioDevice->ioDeviceType.type);
    ui->labelSensorDescription->setText(ioDevice->description);
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}

void DetectionSensorForm::onSensorChange(QChar isLow) {
    if(isLow == '1') {
        qDebug("is low true");
        isLow = true;
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : green }");
    }
    else {
        isLow = false;
        qDebug("is low false");
        ui->labelColorStatus->setStyleSheet("QLabel { background-color : red }");
    }
}