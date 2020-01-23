#include "statemachinetab.h"


StateMachineTab::StateMachineTab(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f)  {

    vbox = new QVBoxLayout(this);
    setLayout(vbox);

    pavementMachine = new BsfPavementMachine;

    createToolbar();
    initStateMachineTab();
}

/** CREATE UI */
void StateMachineTab::createToolbar() {
    stateTabToolbar = new QToolBar;
    stateTabToolbar->setMinimumSize(this->width(), 200);
    stateTabToolbar->move(25, 25);

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

    vbox->addWidget(stateTabToolbar, 1, Qt::AlignTop);
}

void StateMachineTab::initStateMachineTab() {
    stateMachinePage = new StateMachinePage(this, Qt::Widget);
    vbox->addWidget(stateMachinePage, 1, Qt::AlignHCenter);
}

/** PUBLIC SLOTS */
void StateMachineTab::onActHome() {

}

void StateMachineTab::onActGoBack() {

}

void StateMachineTab::onActStartNewPavement() {

}
