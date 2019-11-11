#ifndef LOGTABLEWIDGET_H
#define LOGTABLEWIDGET_H

#include "incl/model/logtablemodel.h"
#include "incl/ui/tabs/logtab.h"
#include "incl/ui/tabs/arduinotab.h"
#include "incl/ui/tabs/recipetab.h"
#include "incl/ui/tabs/iodevicetab.h"
#include <QItemSelection>
#include <QStatusBar>
#include <QTabWidget>
#include <incl/ui/tabs/controlpaneltab.h>

class QTabWidget;

class MainTabBarWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainTabBarWidget(QWidget *parent = nullptr);

public slots:

private slots:

private:
    void setupTabs();
    void getSampleData(int index);

    ControlPanelTab *controlPanelTab{};
    ArduinoTab *arduinoTab{};
    IODeviceTab *ioDeviceTab{};
    RecipeTab *recipeTab{};
    LogTab *logTab{};

    //Sockets
    QUdpSocket *udpSocket = nullptr;

protected:

};

#endif // LOGTABLEWIDGET_H
