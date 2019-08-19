#include "maintabbarwidget.h"

#include <QSortFilterProxyModel>
#include <QtWidgets>


MainTabBarWidget::MainTabBarWidget(QWidget *parent)
    : QTabWidget (parent)
{
    // ToDo wire up events
//    connect(newAddressTab, &NewAddressTab::sendDetails,
//        this, &AddressWidget::addEntry);

    setupTabs();
}

void MainTabBarWidget::setupTabs()
{
    arduinoTab = new ArduinoTab(this);
    addTab(arduinoTab, tr("Arduino's"));

    ioDeviceTab = new IODeviceTab(this);
    addTab(ioDeviceTab, tr("I/O Devices"));

    recipeTab = new RecipeTab(this);
    addTab(recipeTab, tr("Recepten"));

    logTab = new LogTab(this);
    addTab(logTab, tr("Logs"));
}
