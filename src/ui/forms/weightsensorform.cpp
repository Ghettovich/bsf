#include "ui_weightsensorform.h"
#include "incl/ui/forms/weightsensorform.h"

WeightSensorForm::WeightSensorForm(QWidget *parent, IODevice *_ioDevice) :
        QWidget(parent), ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);
    ioDevice = _ioDevice;
}

WeightSensorForm::~WeightSensorForm() {
    delete ui;
}
