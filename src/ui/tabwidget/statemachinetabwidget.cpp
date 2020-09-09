#include "statemachinetabwidget.h"

StatemachineTabWidget::StatemachineTabWidget(QWidget *parent) : QTabWidget(parent) {
    networkService = new NetworkService(this);
    QObject::connect(networkService, &NetworkService::sendArduinoWithNewStates,
                     this, &StatemachineTabWidget::updateArduinoWithIODeviceList);

    createTabWdigetPages();
    createStatemachinePage();

    QObject::connect(this, SIGNAL(currentChanged(int)),this, SLOT(onTabWdigetCurrentChanged(int)));
}

void StatemachineTabWidget::createTabWdigetPages() {
    statemachinePage = new QWidget;
    addTab(statemachinePage, "Start");
    weightSensorPage = new QWidget;
    addTab(weightSensorPage, "Weegcellen");
    detectionSensorPage = new QWidget;
    addTab(detectionSensorPage, "Sensoren");
    relayPage = new QWidget;
    addTab(relayPage, "Relay");
    bunkerPage = new QWidget;
    addTab(bunkerPage, "Bunkers");

    setTabPosition(QTabWidget::West);
    show();
}

void StatemachineTabWidget::createStatemachinePage() {
    statemachinePageWidget = new StateMachinePage(statemachinePage, Qt::Widget);

    QObject::connect(statemachinePageWidget, &StateMachinePage::requestIODeviceStates,
                     this, &StatemachineTabWidget::onRequestIODeviceState);

    statemachinePageWidget->initializePage();
}

void StatemachineTabWidget::createWeightSensorPage() {

}

void StatemachineTabWidget::onTabWdigetCurrentChanged(int index) {
    printf("\nstatemachine tabwidget index changed!\nIndex = %d", index);
    printf("\nHellurr");
}

void StatemachineTabWidget::onRequestIODeviceState(const Arduino& arduino) {
    printf("\nFinished with page, requesting states now");
    networkService->requestPayload(arduino);
}

void StatemachineTabWidget::updateArduinoWithIODeviceList(int arduinoId, Arduino::ARDUINO_STATE newState,
                                                          const QVector<IODevice *> &ioDeviceList) {
    if(currentIndex() == 0) {
        statemachinePageWidget->onUpdateArduinoWithIODeviceList(arduinoId, newState, ioDeviceList);
    } else {
        printf("\nWell... it's not zero.");
    }
}


