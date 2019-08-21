#include "maintabbarwidget.h"

#include <QSortFilterProxyModel>
#include <QtWidgets>

MainTabBarWidget::MainTabBarWidget(QWidget *parent)
    : QTabWidget (parent)
{
    // ToDo wire up events        
    setupTabs();
}

void MainTabBarWidget::setupTabs()
{
    arduinoTab = new ArduinoTab(this);
    addTab(arduinoTab, tr("Arduino's"));
    ioDeviceTab = new IODeviceTab(this);
    addTab(ioDeviceTab, tr("I/O Apparaten"));
    recipeTab = new RecipeTab(this);
    addTab(recipeTab, tr("Recepten"));
    logTab = new LogTab(this);
    addTab(logTab, tr("Logs"));
    // Set arduino tab as current
    setCurrentWidget(arduinoTab);
}

void MainTabBarWidget::currentChanged(int index)
{
    switch (index) {
        case 0:
            setCurrentWidget(arduinoTab);
        break;
        case 1 :
            setCurrentWidget(ioDeviceTab);
        break;
        case 2 :
            setCurrentWidget(recipeTab);
        break;
        case 3 :
            setCurrentWidget(logTab);
        break;
        default:
            setStatusTip(tr("Tab niet gevonden"));
        break;

    }
    addTab(new RecipeTab(this), tr("oneMore"));
}
