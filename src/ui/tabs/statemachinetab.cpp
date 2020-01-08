
#include "incl/ui/tabs/statemachinetab.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>

StateMachineTab::StateMachineTab(QWidget *parent) : QTabWidget(parent) {
    ioDeviceRepository = new IODeviceRepository;
    recipeRepository = new RecipeRepository;

    int arduino_id = 1;
    ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino_id);
    recipeList = recipeRepository->getRecipes();

    // State machine
    pavementMachine = new BsfPavementMachine;
    pavementMachine->getStateObject()->setIoDeviceList(ioDeviceList);

    payloadService.setStateObject(pavementMachine->getStateObject());

    QObject::connect(&payloadService, &PayloadService::onUpdateStateMachineTab,
                     this, &StateMachineTab::onReceiveIODeviceDtoList);

    // Create UI elements
    createSelectRecipeGroupBox();
    createBinLoadGroupBox();

    payloadService.requestStatePayload();
}

void StateMachineTab::fillRecipeComboBox() {
    for (const auto &r: recipeList) {
        comboBoxRecipe->addItem(r.getDescription());
    }
}

void StateMachineTab::createSelectRecipeGroupBox() {
    grpboxSelectRecipe = new QGroupBox("Selecteer recept", this);
    grpboxSelectRecipe->move(5, 5);

    auto *hbox = new QHBoxLayout(grpboxSelectRecipe);

    comboBoxRecipe = new QComboBox(grpboxSelectRecipe);
    fillRecipeComboBox();
    hbox->addWidget(comboBoxRecipe);

    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
        if (sensorLiftLoadId == dev->getId()) {
            binLoadedDetectionSensorForm = new DetectionSensorForm(this, dev);
            hbox->addWidget(binLoadedDetectionSensorForm);
        } else if (relayLiftDownId == dev->getId()) {
            relayFormLiftDown = new RelayForm(this, dev);
            hbox->addWidget(relayFormLiftDown);
        }
    }

    btnStart = new QPushButton("start", grpboxSelectRecipe);
    hbox->addWidget(btnStart);
    connect(btnStart, SIGNAL(clicked()), this, SLOT(onClickStart()));

    connect(comboBoxRecipe, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSelectRecipeCombobox(int)));

    grpboxSelectRecipe->setLayout(hbox);
}

void StateMachineTab::createBinLoadGroupBox() {
    grpboxBinLoading = new QGroupBox("Bin status", this);
    grpboxBinLoading->move(5, 230);
    grpboxBinLoading->setEnabled(false);

    auto *hbox = new QHBoxLayout(grpboxBinLoading);

    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
        if (relayLiftUpId == dev->getId()) {
            relayFormLiftUp = new RelayForm(this, dev);
            hbox->addWidget(relayFormLiftUp);
        } else if (sensorLiftDropId == dev->getId()) {
            binDropDetectionSensorForm = new DetectionSensorForm(this, dev);
            hbox->addWidget(binDropDetectionSensorForm);
        } else if (sensorWeightId == dev->getId()) {
            weightSensorForm = new WeightSensorForm;
            hbox->addWidget(weightSensorForm);
        }
    }

    grpboxBinLoading->setLayout(hbox);
}

// using recipe desc for now
void StateMachineTab::onSelectRecipeCombobox(int comboBoxItemId) {
    printf("on select %d", comboBoxItemId);
    payloadService.requestStatePayload();
}

void StateMachineTab::onReceiveIODeviceDtoList(const QList<IODeviceDTO *> &_ioDeviceDtoList) {
    qInfo() << "got dto's in statetab";
    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
        for (auto dto : _ioDeviceDtoList) {
            if (dev->getId() == dto->id) {
                qInfo() << "found match with iodevice in database and dto";
                emit dev->deviceStateValueChanged(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
            }
        }
    }

    setStatusTip(pavementMachine->stateMessage());
}

void StateMachineTab::onClickStart() {
    if (binLoadedDetectionSensorForm->getDeviceState() == IODeviceState::LOW) {
        auto rInfoData = new RecipeInfoData;
        rInfoData->recipe = &recipeList[0];
        pavementMachine->setPavementRecipe(rInfoData);
        grpboxBinLoading->setEnabled(true);
    } else {
        setStatusTip("Send lift to bottom to continue");
    }
}
