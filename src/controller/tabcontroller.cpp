#include <incl/controller/tabcontroller.h>
#include "incl/model/logtablemodel.h"
#include "incl/ui/tabs/logtab.h"
#include "incl/ui/tabs/arduinotab.h"
#include "incl/ui/tabs/recipetab.h"
#include "incl/ui/tabs/iodevicetab.h"
#include "incl/ui/tabs/controlpaneltab.h"

TabController::TabController(QWidget *_parent) {
    parentWidget = _parent;
}

void TabController::createBsfTabs() {
    mainTabbarWidget = new MainTabBarWidget(parentWidget);

    auto *ioDeviceTab = new IODeviceTab(mainTabbarWidget);
    auto *arduinoTab = new ArduinoTab(mainTabbarWidget);
    auto *controlPanelTab = new ControlPanelTab(mainTabbarWidget);
    auto *recipeTab = new RecipeTab(mainTabbarWidget);
    auto *logTab = new LogTab(mainTabbarWidget);

    for (int i = 0; i < tabNames->length(); ++i) {
        switch (i) {
            case 0 :
                mainTabbarWidget->addTab(ioDeviceTab, tabNames[i]);
                break;
            case 1 :
                mainTabbarWidget->addTab(arduinoTab, tabNames[i]);
                break;
            case 2 :
                mainTabbarWidget->addTab(controlPanelTab, tabNames[i]);
                break;
            case 3 :
                mainTabbarWidget->addTab(recipeTab, tabNames[i]);
                break;
            case 4 :
                mainTabbarWidget->addTab(logTab, tabNames[i]);
                break;
            default:
                break;
        }
    }
}

MainTabBarWidget *TabController::getMainTabbarWidget() const {
    return mainTabbarWidget;
}
