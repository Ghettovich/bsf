
#include <incl/ui/forms/relayform.h>
#include "incl/controller/relaycontroller.h"

void RelayController::createTestRelayWidgets() {
    grid = new QGridLayout;
    grid->setRowMinimumHeight(0, 250);
    QList<ArduinoAction> arduinoActions = actionArduinoRepository->getAllArduinoAction();

    for (int i = 0; i < arduinoActions.length(); ++i) {
        auto *relayForm = new RelayForm(*this);
        relayForm->initWidget(arduinoActions[i]);
        if(i == 0) {
            grid->addWidget(relayForm, 0, 0, Qt::AlignLeft);
        }
        if(i == 1) {
            grid->addWidget(relayForm, 0, 1, Qt::AlignLeft);
        }
        if(i == 2) {
            grid->addWidget(relayForm, 0, 2, Qt::AlignLeft);
        }
        if(i == 3) {
            grid->addWidget(relayForm, 1, 0, Qt::AlignLeft);
        }
        if(i == 4) {
            grid->addWidget(relayForm, 1, 1, Qt::AlignLeft);
        }
        if(i == 5) {
            grid->addWidget(relayForm, 1, 2, Qt::AlignLeft);
            // TODO: remove break and create function to properly build rows and columns
            break;
        }
    }
}


