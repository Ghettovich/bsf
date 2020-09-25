#include "ui_weightsensorform.h"
#include "weightsensorform.h"

#include <utility>

WeightSensorForm::WeightSensorForm(QWidget * parent, const Qt::WindowFlags &f, WeightSensor &pWeightCensor) :
        QWidget(parent)
        , weightSensor(pWeightCensor)
        , ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);
    this->setProperty("weightsensor-id", QVariant(weightSensor.getId()));
    //displayedComponentId = weightSensor.getRecipe().componentList.first().getComponentId();
}
WeightSensorForm::~WeightSensorForm() {
    delete ui;
}

void WeightSensorForm::onUpdateDigitalDisplayWeight(int weight) {
    ui->lcdNumber->display(weight);
    printf("unknown component, but atleast we got a call... which is nice.");
}

void WeightSensorForm::updateWeightSensorForm(WeightSensor &_weightSensor, Arduino::ARDUINO_STATE state) {
    weightSensor.setDeviceState(_weightSensor.getDeviceState());
    weightSensor.getRecipe().updateComponents(_weightSensor.getRecipe().componentList);

    for(const auto& recipeComp : _weightSensor.getRecipe().componentList) {
        if(recipeComp.getComponentId() == displayedComponentId) {
            onUpdateDigitalDisplayWeight(recipeComp.getTargetWeight());
        }
    }

    weightSensor.getArduino()->setArduinoState(state);

    switch (state) {
        case Arduino::READY :
            setStatusTip("Arduino ready for selecting recipe.");
        break;
        case Arduino::RECIPE_SET :
            setStatusTip("Recipe is set, start weighing!");
        break;
        case Arduino::RECIPE_TARGETS_MET :
            setStatusTip("Targets are met please proceed :).");
        break;
        default:
            setStatusTip("Unkown state D:.");
            break;
    }
}
