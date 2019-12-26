
#include <incl/ui/tabs/statemachinetab.h>
#include <QtWidgets/QWidget>

StateMachineTab::StateMachineTab(QWidget *parent) : QTabWidget(parent) {
    pavementMachine = new BsfPavementMachine;

    btnIncrementWeight = new QPushButton("increment", this);
    btnIncrementWeight->move(25, 25);
    connect(btnIncrementWeight, SIGNAL(clicked()), this, SLOT(onIncrementWeight()));

    btnDecreaseWeight = new QPushButton ("decrease", this);
    btnDecreaseWeight->move(25, 75);
    connect(btnDecreaseWeight, SIGNAL(clicked()), this, SLOT(onDecreaseWeight()));
}

void StateMachineTab::onIncrementWeight() {
    auto *data = new RecipeData();
    data->id = 1;
    data->weight++;
    pavementMachine->setWeight(data);
}

void StateMachineTab::onDecreaseWeight() {
    auto *data = new RecipeData();
    data->id = 1;
    data->weight--;
    pavementMachine->setWeight(data);
}

