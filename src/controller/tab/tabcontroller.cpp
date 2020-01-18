#include "tabcontroller.h"
#include <ui/tabs/arduinotab.h>
#include <ui/tabs/logtab.h>
#include <ui/tabs/iodevicetab.h>
//#include <incl/ui/tabs/recipetab.h>
//#include <incl/ui/tabs/controlpaneltab.h>
//#include <incl/ui/tabs/statemachinetab.h>

TabController::TabController(QWidget *_parent) {
    parentWidget = _parent;
}

void TabController::createBsfTabs() {
    mainTabbarWidget = new MainTabBarWidget(parentWidget);
    connect(mainTabbarWidget, SIGNAL(currentChanged),
            this, SLOT(onChangeTab));

    auto *ioDeviceTab = new IODeviceTab(mainTabbarWidget);
    auto *arduinoTab = new ArduinoTab(mainTabbarWidget);
//    auto *controlPanelTab = new ControlPanelTab(mainTabbarWidget);
//    auto *recipeTab = new RecipeTab(mainTabbarWidget);
    auto *logTab = new LogTab(mainTabbarWidget);
//    auto *stateMachineTab = new StateMachineTab(mainTabbarWidget);

    for (int i = 0; i < tabNames->length(); ++i) {
        switch (i) {
            case 0 :
                mainTabbarWidget->addTab(ioDeviceTab, tabNames[i]);
                break;
            case 1 :
                mainTabbarWidget->addTab(arduinoTab, tabNames[i]);
                break;
//            case 2 :
//                mainTabbarWidget->addTab(controlPanelTab, tabNames[i]);
//                break;
//            case 3 :
//                mainTabbarWidget->addTab(recipeTab, tabNames[i]);
//                break;
            case 4 :
                mainTabbarWidget->addTab(logTab, tabNames[i]);
                break;
//            case 5 :
//                mainTabbarWidget->addTab(stateMachineTab, tabNames[i]);
//                break;
            default:
                break;
        }
    }
}

MainTabBarWidget *TabController::getMainTabbarWidget() const {
    return mainTabbarWidget;
}

void TabController::onChangeTab(int index) {
    qDebug("index changed");
}
