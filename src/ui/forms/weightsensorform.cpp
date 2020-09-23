#include "ui_weightsensorform.h"
#include "weightsensorform.h"

#include <utility>

WeightSensorForm::WeightSensorForm(QWidget * parent, const Qt::WindowFlags &f, WeightCensor &pWeightCensor) :
        QWidget(parent)
        , weightCensor(pWeightCensor)
        , ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);
    this->setProperty("weightsensor-id", QVariant(weightCensor.getId()));
}
WeightSensorForm::~WeightSensorForm() {
    delete ui;
}

void WeightSensorForm::onUpdateDigitalDisplayWeight(int componentId, int weight) {
    if(weightCensor.getRecipe().actualComponentMap.contains(componentId)) {
        ui->lcdNumber->display(weight);
    } else {
        printf("unknown component, but atleast we got a call... which is nice.");
    }
}
