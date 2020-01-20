
#include "statemachinetab.h"
#include <domain/iodevicetype.h>
#include <repo/iodevicerepo.h>
#include <repo/reciperepo.h>

StateMachineTab::StateMachineTab() {

    IODeviceRepository ioDeviceRepository;
    RecipeRepository recipeRepository;

    ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduinoFeederAndLiftId);
    ioDeviceWeightStationList = ioDeviceRepository.getArduinoIODeviceList(arduinoWeightStationId);
    weightSensorList = ioDeviceRepository.getArduinoWeightSensorList(arduinoWeightStationId);
    recipeList = recipeRepository.getRecipes();

    // State machine
    pavementMachine = new BsfPavementMachine;
    pavementMachine->getStateObject()->setIoDeviceList(ioDeviceList);
    pavementMachine->getStateObject()->setIoDeviceListWeightStation(ioDeviceWeightStationList);
    pavementMachine->getStateObject()->setWeightSensorList(weightSensorList);

    payloadService.setStateObject(pavementMachine->getStateObject());

//    QObject::connect(&payloadService, &PayloadService::onUpdateStateMachineTab,
//                     this, &StateMachineTab::onReceiveIODeviceDtoList);

    connect(&payloadService, &PayloadService::onReceiveWeightStationReply,
            this, &StateMachineTab::onReceiveFoundWeightStation);

    // Create UI elements
    createSelectRecipeGroupBox();
    createBinLoadGroupBox();

    payloadService.requestStatePayload(ioDeviceList[0]->getArduino(), "");
}

void StateMachineTab::fillRecipeComboBox() {
    for (const auto &r: recipeList) {
        comboBoxRecipe->addItem(r->getDescription());
    }
}

void StateMachineTab::createSelectRecipeGroupBox() {
    grpboxSelectRecipe = new QGroupBox("Selecteer recept", this);
    grpboxSelectRecipe->move(5, 5);

    hbox = new QHBoxLayout(grpboxSelectRecipe);

    comboBoxRecipe = new QComboBox(grpboxSelectRecipe);
    fillRecipeComboBox();
    hbox->addWidget(comboBoxRecipe);

    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
        if (sensorLiftLoadId == dev->getId()) {
            binLoadedDetectionSensorForm = new DetectionSensorForm(dev);
            hbox->addWidget(binLoadedDetectionSensorForm);
        } else if (relayLiftDownId == dev->getId()) {
            relayFormLiftDown = new RelayForm(dev);
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
    grpboxBinLoading->move(5, 225);
    grpboxBinLoading->setEnabled(false);

    hbox = new QHBoxLayout(grpboxBinLoading);

    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
        if (relayLiftUpId == dev->getId()) {
            relayFormLiftUp = new RelayForm(dev);
            hbox->addWidget(relayFormLiftUp);
        } else if (sensorLiftDropId == dev->getId()) {
            binDropDetectionSensorForm = new DetectionSensorForm(dev);
            hbox->addWidget(binDropDetectionSensorForm);
        }
    }

    // ioDeviceWeightStation list is present but unused and still contains a single ioDevice that is the weight sensor
    // but it is not used to send data to app, also it used to retrieved second arduino info like IP address
    for(auto weightSensor: pavementMachine->getStateObject()->getWeightSensorList()) {
        // load cell id = 1, note that only a single component can be chosen at weight station
        // multiple load cells can and probably will be used but the data will be aggregated in Arduino
        if (loadCellId == weightSensor->getId()) {
            if(selectedRecipe == nullptr) {
                selectedRecipe = recipeList[0];
            }

            weightSensorForm = new WeightSensorForm(weightSensor);
            weightSensor->setRecipe(selectedRecipe);
            hbox->addWidget(weightSensorForm);
        }
    }

    grpboxBinLoading->setLayout(hbox);
}

void StateMachineTab::createIODeviceForms() {
    // build tab based on state
}

// using recipe desc for now
void StateMachineTab::onSelectRecipeCombobox(int comboBoxItemId) {
    printf("on select %d", comboBoxItemId);
    selectedRecipe = recipeList[0];
    //payloadService.requestStatePayload(ioDeviceList[0]->getArduino());
}

void StateMachineTab::onClickStart() {
    if (binLoadedDetectionSensorForm->getDeviceState() == IODevice::LOW) {
        auto rInfoData = new RecipeInfoData;
        rInfoData->recipe = recipeList[0];
        pavementMachine->setPavementRecipe(rInfoData);
        grpboxBinLoading->setEnabled(true);
        // should refactor Arduino and add io device list as member of arduino
        payloadService.broadcastRecipe(selectedRecipe, ioDeviceWeightStationList[0]->getArduino());
    } else {
        setStatusTip("Send lift to bottom to continue");
    }
}

void StateMachineTab::onReceiveFoundWeightStation(const QByteArray &reply) {
    qInfo() << "got reply: " << reply.data();
}
