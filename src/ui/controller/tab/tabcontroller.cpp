#include "tabcontroller.h"
#include <ui/tabs/arduinotab.h>
#include <ui/tabs/iodevicetab.h>
#include <ui/tabs/logtab.h>
#include <ui/tabs/recipetab.h>
#include <ui/tabs/statemachinetab.h>

TabController::TabController(QWidget *parent) :
        QObject(parent), hbox(new QHBoxLayout) {
}

void TabController::createBsfTabs(QWidget *parent) {
    mainTabBar = new QTabWidget(parent);

    QObject::connect(mainTabBar, &QTabWidget::currentChanged,
                     this, &TabController::onChangeTab);

    mainTabBar->show();

    ioDevicePage = new QWidget;
    mainTabBar->addTab(ioDevicePage, tabNames[0]);

    arduinoPage = new QWidget;
    mainTabBar->addTab(arduinoPage, tabNames[1]);

    recipePage = new QWidget;
    mainTabBar->addTab(recipePage, tabNames[2]);

    logPage = new QWidget;
    mainTabBar->addTab(logPage, tabNames[3]);

    statemachinePage = new QWidget;
    mainTabBar->addTab(statemachinePage, tabNames[4]);
}

QWidget *TabController::getCurrentPage() const {
    return mainTabBar;
}

void TabController::onChangeTab(int index) {
    if (mainTabBar->currentWidget() != nullptr) {
        while (!hbox->isEmpty()) {
            auto w = hbox->takeAt(0)->widget();
            w->deleteLater();
        }
    }

    if (index == 0)
        createIODevicePage();
    else if (index == 1)
        createArduinoPage();
    else if (index == 2)
        createRecipePage();
    else if (index == 3)
        createLogPage();
    else if (index == 4)
        createStatemachinePage();
    else
        printf("unknown index %d", index);
}

void TabController::createIODevicePage() {
    auto ioDeviceTab = new IODeviceTab(ioDevicePage, Qt::Widget);
    hbox->addWidget(ioDeviceTab);
    ioDevicePage->setLayout(hbox);
}

void TabController::createArduinoPage() {
    auto arduinoTab = new ArduinoTab(arduinoPage, Qt::Widget);
    hbox->addWidget(arduinoTab);
    arduinoPage->setLayout(hbox);
}

void TabController::createRecipePage() {
    auto recipeTab = new RecipeTab(recipePage, Qt::Widget);
    hbox->addWidget(recipeTab);
    recipePage->setLayout(hbox);
}

void TabController::createLogPage() {
    auto logTab = new LogTab(logPage, Qt::Widget);
    hbox->addWidget(logTab);
    logPage->setLayout(hbox);
}

void TabController::createStatemachinePage() {
    auto statemachineTab = new StateMachineTab(statemachinePage, Qt::Widget);
    hbox->addWidget(statemachineTab);
    statemachinePage->setLayout(hbox);
}
