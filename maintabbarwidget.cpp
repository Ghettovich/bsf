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
}
