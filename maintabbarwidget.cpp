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
    addTab(new IODeviceTab, tr("Arduino's"));

    addTab(new IODeviceTab, tr("I/O Devices"));

    addTab(new RecipeTab, tr("Recepten"));

    addTab(new LogTab, tr("Logs"));

}


