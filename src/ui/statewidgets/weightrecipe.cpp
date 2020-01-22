#include "weightrecipe.h"



WeighRecipe::WeighRecipe(QWidget *parent, const Qt::WindowFlags &f, PavementStateObject *_stateObject) :
        QWidget(parent, f) {
    createBinLoadGroupBox();
}

void WeighRecipe::createBinLoadGroupBox() {
    grpboxBinLoading = new QGroupBox("Bin status", this);
    grpboxBinLoading->move(5, 225);
    grpboxBinLoading->setEnabled(false);

    hbox = new QHBoxLayout(grpboxBinLoading);

//    for (auto dev : pavementMachine->getStateObject()->getIoDeviceList()) {
//        if (relayLiftUpId == dev->getId()) {
//            relayFormLiftUp = new RelayForm(dev);
//            hbox->addWidget(relayFormLiftUp);
//        } else if (sensorLiftDropId == dev->getId()) {
//            binDropDetectionSensorForm = new DetectionSensorForm(dev);
//            hbox->addWidget(binDropDetectionSensorForm);
//        }
//    }

    // ioDeviceWeightStation list is present but unused and still contains a single ioDevice that is the weight sensor
    // but it is not used to send data to app, also it used to retrieved second arduino info like IP address
//    for(auto weightSensor: pavementMachine->getStateObject()->getWeightSensorList()) {
//        // load cell id = 1, note that only a single component can be chosen at weight station
//        // multiple load cells can and probably will be used but the data will be aggregated in Arduino
//        if (loadCellId == weightSensor->getId()) {
//            if(selectedRecipe == nullptr) {
//                selectedRecipe = recipeList[0];
//            }
//
//            weightSensorForm = new WeightSensorForm(weightSensor);
//            weightSensor->setRecipe(selectedRecipe);
//            hbox->addWidget(weightSensorForm);
//        }
//    }

    grpboxBinLoading->setLayout(hbox);
}
