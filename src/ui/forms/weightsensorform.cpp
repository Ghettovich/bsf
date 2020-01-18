#include "ui_weightsensorform.h"
#include "weightsensorform.h"

WeightSensorForm::WeightSensorForm(QWidget *parent, WeightCensor *pWeightCensor) :
        QWidget(parent), weightCensor(pWeightCensor), ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);

    //connect(ioDevice, &IODevice::deviceStateValueChanged, this, &DetectionSensorForm::setIODeviceState);
    connect(weightCensor, &WeightCensor::updateRecipeWithComponentData,
            this, &WeightSensorForm::onUpdateDigitalDisplayWeight);
}
WeightSensorForm::~WeightSensorForm() {
    delete ui;
}

void WeightSensorForm::onUpdateDigitalDisplayWeight(int componentId, int weight) {
    if(weightCensor->getRecipe()->getPlastifierId() == componentId) {
        ui->lcdNumber->display(weight);
    } else {
        printf("unknown component, but atleast we got a call... which is nice.");
    }
}
