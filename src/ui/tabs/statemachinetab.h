#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <ui/statewidgets/statemachinepage.h>
#include <ui/statewidgets/selectrecipe.h>
#include <ui/statewidgets/weightrecipe.h>
#include <statemachine/bsfpavementmachine.h>
#include <QObject>
#include <QFlags>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>


class StateMachineTab : public QWidget {

    Q_OBJECT

public:
    StateMachineTab(QWidget *parent, const Qt::WindowFlags &f);

public slots:
    void onActHome();
    void onActGoBack();
    void onActStartNewPavement();

private:
    QToolBar *stateTabToolbar = nullptr;
    QAction *homeAct = nullptr;
    QAction *goBackAct = nullptr;
    QAction *startNewPavementAct = nullptr;
    QGridLayout *gridLayout = nullptr;
    BsfPavementMachine *pavementMachine;
    // State widgets
    StateMachinePage *stateMachinePage = nullptr;

    void initStateMachineTab();
    void createToolbar();

};

#endif //BSF_STATEMACHINETAB_H
