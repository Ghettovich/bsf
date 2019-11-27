#include "ui_detectionsensorform.h"
#include <incl/ui/forms/detectionsensorform.h>

DetectionSensorForm::DetectionSensorForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent)
        , ui(new Ui::DetectionSensorForm) {
    ui->setupUi(this);
    qDebug("%s", qUtf8Printable("called constructor detection sensor widget..."));
    ioDevice = _ioDevice;
    ui->labelStatus->setText("STATUS");
}

DetectionSensorForm::~DetectionSensorForm() {
    delete ui;
}
