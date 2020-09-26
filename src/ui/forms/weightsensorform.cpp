#include "ui_weightsensorform.h"
#include "weightsensorform.h"

//#include <utility>
#include <repo/reciperepo.h>
#include <QtWidgets/QHeaderView>

WeightSensorForm::WeightSensorForm(QWidget * parent, const Qt::WindowFlags &f, WeightSensor &pWeightCensor) :
        QWidget(parent)
        , weightSensor(pWeightCensor)
        , payloadService(this)
        , ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);
    this->setProperty("weightsensor-id", QVariant(weightSensor.getId()));
    RecipeRepository recipeReposiory;
    recipeList = recipeReposiory.getRecipes();

    QObject::connect(ui->pushButtonSaveRecipe, SIGNAL(clicked()),
                     this, SLOT(onClickSetSetRecipe()));

    QObject::connect(ui->recipeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onRecipeComboBoxIndexChanged(int)));

    initRecipeComboBox();
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

    updateTargetsInTableView();
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

void WeightSensorForm::initRecipeComboBox() {
    for(const auto& recipe: recipeList) {
        ui->recipeComboBox->addItem(recipe.getDescription(), recipe.getId());
    }
}

void WeightSensorForm::onRecipeComboBoxIndexChanged(int index) {
    printf("index = %d\n", index);
    if(index != -1) {
        QVariant id = ui->recipeComboBox->currentData(Qt::UserRole);

        RecipeRepository recipeRepository;
        currentRecipe = recipeRepository.getRecipeWithComponents(id.toInt());
        populateTableWithComponents();
    }
}

void WeightSensorForm::populateTableWithComponents() {
    componentTableModel = new TableComponentModel((currentRecipe.componentList));
    ui->recipeTableView->setModel(componentTableModel);
}

void WeightSensorForm::updateTargetsInTableView() {
    for(auto compStruct: componentTableModel->getComponents()) {
        if (currentRecipe.actualComponentMap.contains(compStruct.componentId.toInt())) {
            compStruct.actualWeight = currentRecipe.actualComponentMap.value(compStruct.componentId.toInt());
        }
    }
}

void WeightSensorForm::onClickSetSetRecipe() {
    if(currentRecipe.getId() != 0) {
        payloadService.broadcastRecipe(currentRecipe,
                                       weightSensor.getArduino()->getId(),
                                       weightSensor.getArduino()->getIpAddress(),
                                       weightSensor.getArduino()->getPort());
    }
}
