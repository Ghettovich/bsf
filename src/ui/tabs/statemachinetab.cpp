#include "statemachinetab.h"

StateMachineTab::StateMachineTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f) {

    vbox = new QVBoxLayout(this);
    setLayout(vbox);

    //pavementMachine = new BsfPavementMachine;
    createToolbar();
    initStateMachineTab();
}

/** CREATE UI */
void StateMachineTab::createToolbar() {
    stateTabToolbar = new QToolBar(this);

    homeAct = new QAction(QIcon(":/actions/home_black_48dp.png"),tr("&Home"), this);
    homeAct->setStatusTip(tr("Terug naar start"));

    QObject::connect(homeAct, &QAction::triggered,
                     this, &StateMachineTab::onActHome);
    stateTabToolbar->addAction(homeAct);

    goBackAct = new QAction(QIcon(":/navigation/arrow_back_black_48dp.png"), tr("&Terug"), this);
    goBackAct->setStatusTip(tr("Ga terug"));
    QObject::connect(goBackAct, &QAction::triggered,
                     this, &StateMachineTab::onActGoBack);
    stateTabToolbar->addAction(goBackAct);

    startNewPavementAct = new QAction(tr("&Start"), this);
    startNewPavementAct->setStatusTip(tr("Start"));
    QObject::connect(startNewPavementAct, &QAction::triggered,
                     this, &StateMachineTab::onActStartNewPavement);
    stateTabToolbar->addAction(startNewPavementAct);

    vbox->addWidget(stateTabToolbar, 0, Qt::AlignTop);
}

void StateMachineTab::initStateMachineTab() {
    tabWidget = new StatemachineTabWidget(this);
    vbox->addWidget(tabWidget);
}

/** PUBLIC SLOTS */
void StateMachineTab::onActHome() {

}

void StateMachineTab::onActGoBack() {

}

void StateMachineTab::onActStartNewPavement() {

}
