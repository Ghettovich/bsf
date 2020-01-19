#include "tabcontroller.h"
#include <ui/tabs/recipetab.h>
//#include <ui/tabs/statemachinetab.h>
#include <ui/tabs/arduinotab.h>
#include <ui/tabs/logtab.h>
#include <ui/tabs/iodevicetab.h>

TabController::TabController() : hbox(new QHBoxLayout) {
    //parentWidget = _parent;
    hbox->setObjectName("main");
    qDebug("tab controller constructor");
}

void TabController::createBsfTabs(QWidget *parent) {
    qDebug("creating tabs...");

    mainTabBar = new QTabWidget(parent);
    mainTabBar->show();
    //mainTabBar->setMinimumSize(500, 500);

    ioDevicePage = new QWidget;
    mainTabBar->addTab(ioDevicePage, tabNames[TEST_IO_DEVICES]);

    arduinoPage = new QWidget;
    mainTabBar->addTab(arduinoPage, tabNames[ARDUINOS]);

    recipePage = new QWidget;
    mainTabBar->addTab(recipePage, tabNames[RECIPES]);

    logPage = new QWidget;
    mainTabBar->addTab(logPage, tabNames[LOGS]);

    createIODevicePage();

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
        while(!hbox->isEmpty()) {
            QWidget * w = hbox->takeAt(0)->widget();
            w->deleteLater();
            qDebug("deleted child");
        }

    }

    if (index == TEST_IO_DEVICES)
        createIODevicePage();
    else if (index == ARDUINOS)
        createArduinoPage();
    else if (index == RECIPES)
        createRecipePage();
    else if (index == LOGS)
        createLogPage();
    else if (index == STATEMACHINE)
        createStatemachinePage();
}

void TabController::createIODevicePage() {
    qDebug("creating io device page");
    if (mainTabBar->currentIndex() == TEST_IO_DEVICES) {
        auto ioDeviceTab = new IODeviceTab();
        hbox->addWidget(ioDeviceTab);
        ioDevicePage->setLayout(hbox);
    }
}

void TabController::createArduinoPage() {
    qDebug("creating arduino page");
    if (mainTabBar->currentIndex() == ARDUINOS) {
        auto arduinoTab = new ArduinoTab();
        hbox->addWidget(arduinoTab);
        arduinoPage->setLayout(hbox);
    }
}

void TabController::createRecipePage() {
    qDebug("creating recipes page");
    if (mainTabBar->currentIndex() == RECIPES) {
        auto recipeTab = new RecipeTab();
        hbox->addWidget(recipeTab);
        recipePage->setLayout(hbox);
    }
}

void TabController::createLogPage() {
    qDebug("creating logs page");
    if (mainTabBar->currentIndex() == LOGS) {
        auto logTab = new LogTab();
        hbox->addWidget(logTab);
        logPage->setLayout(hbox);
    }
}

void TabController::createStatemachinePage() {
    statemachineTab = nullptr;
}
