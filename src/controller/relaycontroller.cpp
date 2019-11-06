
#include <incl/domain/action.h>
#include <incl/ui/forms/relayform.h>
#include "relaycontroller.h"

void RelayController::createTestRelayWidgets() {
    grid = new QGridLayout;
    QList<stateAction> stateActions;

    stateAction sa1;
    sa1.id = 1;
    sa1.code = "LIFT_UP";
    sa1.description = "Start lift up";
    stateActions.append(sa1);

    stateAction sa2;
    sa2.id = 2;
    sa2.code = "LIFT_DOWN";
    sa2.description = "Start lift down";
    stateActions.append(sa2);

    stateAction sa3;
    sa3.id = 3;
    sa3.code = "BIN_DUMP";
    sa3.description = "Dump bin in mixer";
    stateActions.append(sa3);

    stateAction sa4;
    sa4.id = 4;
    sa4.code = "BIN_LOAD";
    sa4.description = "Reset bin to load position";
    stateActions.append(sa4);

    grid->setRowMinimumHeight(0, 250);

    for (int i = 0; i < stateActions.length(); ++i) {
        auto *relayForm = new RelayForm(*this);
        relayForm->initWidget(stateActions[i]);
        if(i == 0) {
            grid->addWidget(relayForm, 0, 0, Qt::AlignLeft);
        }
        if(i == 1) {
            grid->addWidget(relayForm, 0, 1, Qt::AlignLeft);
        }
        if(i == 2) {
            grid->addWidget(relayForm, 1, 0, Qt::AlignLeft);
        }
        if(i == 3) {
            grid->addWidget(relayForm, 1, 1, Qt::AlignLeft);
            // TODO: remove break and create function to properly build rows and columns
            break;
        }
    }

//    for(auto sa: stateActions) {
//        auto *relayForm = new RelayForm(*this);
//        relayForm->initWidget(sa);
//        hbox->addWidget(relayForm);
//    }
}


