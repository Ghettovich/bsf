#ifndef BSF_STATEMACHINETAB_H
#define BSF_STATEMACHINETAB_H

#include <statewidgets/statemachinepage.h>
#include <statewidgets/selectrecipe.h>
#include <statewidgets/weightrecipe.h>
#include <tabwidget/statemachinetabwidget.h>
#include <bsfpavementmachine.h>
#include <QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QAction>


class StateMachineTab : public QWidget {

    Q_OBJECT

private:
    QToolBar *stateTabToolbar = nullptr;
    QAction *homeAct = nullptr;
    QAction *goBackAct = nullptr;
    QAction *startNewPavementAct = nullptr;
    QVBoxLayout *vbox = nullptr;
    StatemachineTabWidget *tabWidget = nullptr;

    StateMachinePage *stateMachinePage = nullptr;
    BsfPavementMachine *pavementMachine;

    void createToolbar();
    void initStateMachineTab();

public:
    StateMachineTab(QWidget *parent, const Qt::WindowFlags &f);

public slots:
    void onActHome();
    void onActGoBack();
    void onActStartNewPavement();

};

#endif //BSF_STATEMACHINETAB_H
