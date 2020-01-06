
#include "incl/ui/tabs/statemachinetab.h"
#include <QtWidgets/QWidget>

StateMachineTab::StateMachineTab(QWidget *parent) : QTabWidget(parent) {
    ioDeviceRepository = new IODeviceRepository;
    recipeRepository = new RecipeRepository;

    payloadService = new PayloadService(this);

    // State machine
    pavementMachine = new BsfPavementMachine;

    // Create UI elements
    createRecipeComboBox();

    btnStart = new QPushButton("Start", this);
    btnStart->move(160, 25);
    connect(btnStart, SIGNAL(clicked()), this, SLOT(onStart()));

    btnIncrementWeight = new QPushButton("increment", this);
    btnIncrementWeight->move(25, 100);
    connect(btnIncrementWeight, SIGNAL(clicked()), this, SLOT(onIncrementWeight()));

    btnDecreaseWeight = new QPushButton("decrease", this);
    btnDecreaseWeight->move(25, 150);
    connect(btnDecreaseWeight, SIGNAL(clicked()), this, SLOT(onDecreaseWeight()));

    QObject::connect(payloadService, &PayloadService::onSendIODeviceDtoList,
                     this, &StateMachineTab::onReceiveIODeviceDtoList);
}

void StateMachineTab::createRecipeComboBox() {
    comboBoxRecipe = new QComboBox(this);
    comboBoxRecipe->move(25, 25);
    recipeList = recipeRepository->getRecipes();

    connect(comboBoxRecipe, SIGNAL(activated(int)),
            this, SLOT(onActivtedRecipeCombobox(int)));

    connect(comboBoxRecipe, SIGNAL(currentIndexChanged(int)),
            this, SLOT(onSelectRecipeCombobox(int)));

    for (const auto &r: recipeList) {
        comboBoxRecipe->addItem(r.getDescription());
    }

}

void StateMachineTab::onStart() {
    int arduino_id = 1;
    ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino_id);

    if(ioDeviceList.empty()) {
        qInfo() << "Could not find devices";
    }
    else {

    }
}

void StateMachineTab::onIncrementWeight() {
    auto *data = new RecipeData();
    data->id = 1;
    data->weight++;
    pavementMachine->setWeight(data);
}

void StateMachineTab::onDecreaseWeight() {
    auto *data = new RecipeData();
    data->id = 1;
    data->weight--;
    pavementMachine->setWeight(data);
}

// using recipe desc for now
void StateMachineTab::onSelectRecipeCombobox(int comboBoxItemId) {
    printf("on select %d", comboBoxItemId);

    auto rInfoData = new RecipeInfoData;
    rInfoData->recipe = &recipeList[comboBoxItemId];
    pavementMachine->setPavementRecipe(rInfoData);
    //payloadService->requestStatePayload("http://[fd54:d174:8676:0001:7269:74ff:fe2d:3031]/");
}


void StateMachineTab::onActivtedRecipeCombobox(int comboBoxItemId) {
    printf("on activated %d", comboBoxItemId);
}

void StateMachineTab::onReceiveIODeviceDtoList(const QList<IODeviceDTO *> &_ioDeviceDtoList) {
//    int arduino_id = 1;
//    ioDeviceList = ioDeviceRepository->getArduinoIODeviceList(arduino_id);
//
//
//    for (auto dev : ioDeviceList) {
//        for (auto dto : _ioDeviceDtoList) {
//            if (dev->getId() == dto->id) {
//                qInfo() << "found match with iodevice in database and dto";
//                dev->setDeviceState(dto->low == 1 ? IODeviceState::LOW : IODeviceState::HIGH);
//            }
//        }
//    }
//
//
//    auto rIODeviceData = new IODeviceData;
//
//    rIODeviceData->ioDeviceList = ioDeviceList;
//    // pointers are fucked and state transitions are broken :')
//    pavementMachine->setIODeviceList(rIODeviceData);

}
