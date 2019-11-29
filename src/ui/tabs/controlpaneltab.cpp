#include <QTabWidget>

#include <incl/ui/tabs/controlpaneltab.h>
//#include "incl/controller/relaycontroller.h"

ControlPanelTab::ControlPanelTab(QTabWidget *parent)
        : QWidget(parent) {
    setStatusTip("Operator tab actief");
//    auto *relayController = new RelayController(this);
//    relayController->createTestRelayWidgets();
//    relayController->updateWidgetWithRelayStates();
//    setLayout(relayController->grid);
}

