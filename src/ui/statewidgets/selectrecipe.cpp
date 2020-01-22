//
// Created by Geert on 22 Jan 2020.
//

#include "selectrecipe.h"

SelectRecipe::SelectRecipe(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f) {
    RecipeRepository recipeRepository;

    recipeList = recipeRepository.getRecipes();
    createSelectRecipeGroupBox();

    // ToDo:add method in iodevice repo to fetch device with int array
//    IODeviceRepository ioDeviceRepository;
//    //ioDeviceList = ioDeviceRepository.getArduinoIODeviceList(arduinoFeederAndLiftId);
}

void SelectRecipe::fillRecipeComboBox() {
    for (const auto &r: recipeList) {
        comboBoxRecipe->addItem(r.getDescription());
    }
}

void SelectRecipe::createSelectRecipeGroupBox() {
    grpboxSelectRecipe = new QGroupBox("Selecteer recept", this);
    grpboxSelectRecipe->move(5, 5);

    hbox = new QHBoxLayout(grpboxSelectRecipe);

    comboBoxRecipe = new QComboBox(grpboxSelectRecipe);
    fillRecipeComboBox();
    hbox->addWidget(comboBoxRecipe);

//    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
//        if (sensorLiftLoadId == dev->getId()) {
//            binLoadedDetectionSensorForm = new DetectionSensorForm(dev);
//            hbox->addWidget(binLoadedDetectionSensorForm);
//        } else if (relayLiftDownId == dev->getId()) {
//            relayFormLiftDown = new RelayForm(dev);
//            hbox->addWidget(relayFormLiftDown);
//        }
//    }

    btnStart = new QPushButton("start", grpboxSelectRecipe);
    hbox->addWidget(btnStart);
    connect(btnStart, SIGNAL(clicked()), this, SLOT(onClickContinue()));

    connect(comboBoxRecipe, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSelectRecipeCombobox(int)));

    grpboxSelectRecipe->setLayout(hbox);
}


// ToDo: map index on list instead of desc
// using recipe desc for now
void SelectRecipe::onSelectRecipeCombobox(int index) {

    if(index >= 0) {
        printf("on select %d", index);
        selectedRecipe = recipeList[0];
        //payloadService.requestStatePayload(ioDeviceList[0]->getArduino());
    }
}

void SelectRecipe::onClickContinue() {
//    if (binLoadedDetectionSensorForm->getDeviceState() == IODevice::LOW) {
//        auto rInfoData = new RecipeInfoData;
//        rInfoData->recipe = recipeList[0];
//        pavementMachine->setPavementRecipe(rInfoData);
//        grpboxBinLoading->setEnabled(true);
//        // should refactor Arduino and add io device list as member of arduino
//        payloadService.broadcastRecipe(selectedRecipe, ioDeviceWeightStationList[0]->getArduino());
//    } else {
//        setStatusTip("Send lift to bottom to continue");
//    }
}
