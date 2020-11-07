#include "ui_weightsensorform.h"
#include "weightsensorform.h"
#include <reciperepo.h>
#include <QtWidgets/QHeaderView>

WeightSensorForm::WeightSensorForm(QWidget * parent, const Qt::WindowFlags &f, WeightSensor &pWeightCensor) :
        QWidget(parent)
        , weightSensor(pWeightCensor)
        , ui(new Ui::WeightSensorForm) {
    ui->setupUi(this);
    this->setProperty("weightsensor-id", QVariant(weightSensor.getId()));
    RecipeRepository recipeReposiory;
    recipeList = recipeReposiory.getRecipes();

    QObject::connect(ui->pushButtonSetRecipe, SIGNAL(clicked()),
                     this, SLOT(onClickSetSetRecipe()));

    QObject::connect(ui->recipeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onRecipeComboBoxIndexChanged(int)));

    ui->groupBox->setTitle(weightSensor.getDescription());
    initRecipeComboBox();
}
WeightSensorForm::~WeightSensorForm() {
    delete ui;
}

void WeightSensorForm::onUpdateDigitalDisplayWeight(int weight) {
    ui->lcdNumber->display(weight);
}

void WeightSensorForm::updateWeightSensorForm(WeightSensor &_weightSensor, Arduino::ARDUINO_STATE state) {
    weightSensor.setDeviceState(_weightSensor.getDeviceState());
    currentRecipe.updateComponents(_weightSensor.getRecipe().componentList);

    if(weightSensor.getDeviceState() == IODevice::HIGH) {
        ui->lcdNumber->setStatusTip("Weegschaal beschikbaar.");
    }

    selectedComponent = _weightSensor.getRecipe().getSelectedComponent();
    if(selectedComponent != Component::UNKNOWN_COMP) {
        weightSensor.getRecipe().setSelectedComponent(_weightSensor.getRecipe().getSelectedComponent());
        updateTargetInfo();
    }

    updateTargetsInTableView();
    weightSensor.getArduino()->setArduinoState(state);

    switch (state) {
        case Arduino::READY :
            ui->groupBox->setStatusTip("Arduino ready for selecting recipe.");
        break;
        case Arduino::RECIPE_SET :
            ui->groupBox->setStatusTip("Recipe is set, start weighing!");
        break;
        case Arduino::RECIPE_TARGETS_MET :
            ui->groupBox->setStatusTip("Targets are met please proceed :).");
        break;
        default:
            break;
    }
}

void WeightSensorForm::initRecipeComboBox() {
    for(const auto& recipe: recipeList) {
        ui->recipeComboBox->addItem(recipe.getDescription(), recipe.getId());
    }
}

void WeightSensorForm::onRecipeComboBoxIndexChanged(int index) {
    if(index != -1) {
        QVariant id = ui->recipeComboBox->currentData(Qt::UserRole);

        RecipeRepository recipeRepository;
        currentRecipe = recipeRepository.getRecipeWithComponents(id.toInt());

        selectedComponent = currentRecipe.componentList.first().getRecipeComponent();
        weightSensor.setRecipe(currentRecipe);
        populateTableWithComponents();
    }
}

void WeightSensorForm::populateTableWithComponents() {
    componentTableModel = new TableComponentModel((currentRecipe.componentList));
    ui->recipeTableView->horizontalHeader()->setStretchLastSection(true);
    ui->recipeTableView->setModel(componentTableModel);
    ui->recipeTableView->hideColumn(0);
}

void WeightSensorForm::updateTargetsInTableView() {
    componentTableModel->updateComponentsInTable(currentRecipe.actualComponentMap);
}

void WeightSensorForm::onClickSetSetRecipe() {
    if(currentRecipe.getId() != 0) {
        emit broadcastRecipe(currentRecipe);
    }
}

void WeightSensorForm::updateTargetInfo() {

    for(const auto& comp: currentRecipe.componentList) {
        if(comp.getRecipeComponent() == selectedComponent) {
            int weight = currentRecipe.getActualWeightForComponent(comp.getComponentId());
            onUpdateDigitalDisplayWeight(weight);

            ui->labelTarget->setText(QString::number(comp.getTargetWeight()));
            ui->labelComponent->setText(comp.getComponent());
            break;
        }
    }
}
