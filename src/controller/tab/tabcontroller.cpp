#include "tabcontroller.h"
#include <ui/tabs/arduinotab.h>
#include <ui/tabs/iodevicetab.h>
#include <ui/tabs/logtab.h>
//#include <ui/tabs/recipetab.h>
//#include <ui/tabs/statemachinetab.h>

TabController::TabController(QWidget *parent) :
        QObject(parent), hbox(new QHBoxLayout) {
    //parentWidget = _parent;
    hbox->setObjectName("main");
    qDebug("tab controller constructor");
}

void TabController::createBsfTabs(QWidget *parent) {
    qDebug("creating tabs...");

    mainTabBar = new QTabWidget(parent);
    mainTabBar->show();

    ioDevicePage = new QWidget;
    mainTabBar->addTab(ioDevicePage, tabNames[0]);

    arduinoPage = new QWidget;
    mainTabBar->addTab(arduinoPage, tabNames[1]);
//
//    recipePage = new QWidget;
//    mainTabBar->addTab(recipePage, tabNames[RECIPES]);

    logPage = new QWidget;
    mainTabBar->addTab(logPage, tabNames[3]);

    createLogPage();

    connect(mainTabBar, SIGNAL(currentChanged(int)),
            this, SLOT(onChangeTab(int)));

    qDebug("finished tab");
}

QWidget *TabController::getCurrentPage() const {
    return mainTabBar;
}

void TabController::onChangeTab(int index) {
    qDebug("tab index changed");
    if (mainTabBar->currentWidget() != nullptr) {
        while (!hbox->isEmpty()) {
            auto w = hbox->takeAt(0)->widget();
            w->deleteLater();
            qDebug("deleted child");
        }

    }

    if (index == 0)
        createIODevicePage();
    else if (index == 1)
        createArduinoPage();
    else if (index == 2)
        createLogPage();
//    else if (index == 3)
//        createLogPage();
//    else if (index == 4)
//        createStatemachinePage();
}

void TabController::createIODevicePage() {
    qDebug("creating io device page");
    if (mainTabBar->currentIndex() == 0) {
        auto ioDeviceTab = new IODeviceTab();
        hbox->addWidget(ioDeviceTab);
        ioDevicePage->setLayout(hbox);
    }
}
//
void TabController::createArduinoPage() {
    qDebug("creating arduino page");
    if (mainTabBar->currentIndex() == 1) {
        auto arduinoTab = new ArduinoTab(arduinoPage);
        hbox->addWidget(arduinoTab);
        arduinoPage->setLayout(hbox);
    }
}
//
//void TabController::createRecipePage() {
//    qDebug("creating recipes page");
//    if (mainTabBar->currentIndex() == 2) {
//        auto recipeTab = new RecipeTab();
//        hbox->addWidget(recipeTab);
//        recipePage->setLayout(hbox);
//    }
//}
//
void TabController::createLogPage() {
    qDebug("creating logs page");
    auto logTab = new LogTab;
    hbox->addWidget(logTab);
    logPage->setLayout(hbox);

}
//
//void TabController::createStatemachinePage() {
//    statemachineTab = nullptr;
//}
