#include "statemachinepage.h"
#include <QtWidgets/QLabel>

StateMachinePage::StateMachinePage(QWidget *parent, const Qt::WindowFlags &f) : QWidget(parent, f), gridLayout(new QGridLayout) {
    initStateMachinePage();
    setLayout(gridLayout);
}

void StateMachinePage::initStateMachinePage() {
    auto lblStatusArduino1 = new QLabel("Arduino 1");
    auto lblStatusArduino2 = new QLabel("Arduino 2");
    gridLayout->addWidget(lblStatusArduino1, 0, 0, Qt::AlignLeft);
    gridLayout->addWidget(lblStatusArduino2, 0, 1, Qt::AlignLeft);

    auto lblBunker1 = new QLabel("Zand fijn");
    auto lblBunker2 = new QLabel("Zand grof");
    auto lblBunker3 = new QLabel("Grind fijn");

    gridLayout->addWidget(lblBunker1, 1, 0, Qt::AlignLeft);
    gridLayout->addWidget(lblBunker2, 1, 1, Qt::AlignLeft);
    gridLayout->addWidget(lblBunker3, 1, 2, Qt::AlignLeft);
}

