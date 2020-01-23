#include "statemachinetab.h"


StateMachineTab::StateMachineTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f)  {

    gridLayout = new QGridLayout(this);
    setLayout(gridLayout);

    pavementMachine = new BsfPavementMachine;

    createToolbar();
    initStateMachineTab();
}

/** CREATE UI */
void StateMachineTab::createToolbar() {
    stateTabToolbar = new QToolBar(this);

    //const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
    homeAct = new QAction(tr("&Home"), this);
    homeAct->setStatusTip(tr("Terug naar start"));
    QObject::connect(homeAct, &QAction::triggered,
                     this, &StateMachineTab::onActHome);
    stateTabToolbar->addAction(homeAct);

    goBackAct = new QAction(tr("&Terug"), this);
    goBackAct->setStatusTip(tr("Ga terug"));
    QObject::connect(goBackAct, &QAction::triggered,
                     this, &StateMachineTab::onActGoBack);
    stateTabToolbar->addAction(goBackAct);

    startNewPavementAct = new QAction(tr("&Start"), this);
    startNewPavementAct->setStatusTip(tr("Start"));
    QObject::connect(startNewPavementAct, &QAction::triggered,
                     this, &StateMachineTab::onActStartNewPavement);
    stateTabToolbar->addAction(startNewPavementAct);

    gridLayout->addWidget(stateTabToolbar, 0, 0, Qt::AlignLeft);
}

void StateMachineTab::initStateMachineTab() {
    stateMachinePage = new StateMachinePage(this, Qt::Widget);
    gridLayout->addWidget(stateMachinePage, 1, 0,  Qt::AlignHCenter);
}

/** PUBLIC SLOTS */
void StateMachineTab::onActHome() {

}

void StateMachineTab::onActGoBack() {

}

void StateMachineTab::onActStartNewPavement() {

}
