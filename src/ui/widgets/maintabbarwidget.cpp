#include "incl/ui/widgets/maintabbarwidget.h"
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

    controlPanelTab = new ControlPanelTab(this);
    addTab(controlPanelTab, tr("Control panel"));

    ioDeviceTab = new IODeviceTab(this);
    addTab(ioDeviceTab, tr("Test paneel"));

    recipeTab = new RecipeTab(this);
    addTab(recipeTab, tr("Recepten"));

    logTab = new LogTab(this);
    addTab(logTab, tr("Logs"));

    connect(this, &QTabWidget::currentChanged, this, &MainTabBarWidget::getSampleData);
}

void MainTabBarWidget::getSampleData(int index)
{
    if(index == 3) {
        logTab->createSampleData();
    }

}
