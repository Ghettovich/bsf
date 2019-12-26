#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <incl/statemachine/bsfpavementmachine.h>

class StateMachineTab : public QTabWidget {

    Q_OBJECT

public:
    explicit StateMachineTab(QWidget *parent = nullptr);

private:
    BsfPavementMachine *pavementMachine;
    QPushButton * btnIncrementWeight = nullptr;
    QPushButton * btnDecreaseWeight = nullptr;

private slots:
    void onIncrementWeight();
    void onDecreaseWeight();

};
#endif //BSF_STATEMACHINETAB_H
