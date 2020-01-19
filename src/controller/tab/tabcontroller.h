#ifndef BSF_TABCONTROLLER_H
#define BSF_TABCONTROLLER_H

#include <QObject>
#include <QString>
#include <QHBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class TabController : public QObject {

    Q_OBJECT

    enum TabIndexes { TEST_IO_DEVICES = 0, ARDUINOS = 1, RECIPES = 2, LOGS = 3, STATEMACHINE = 4 };

public:
    explicit TabController();
    QWidget *getCurrentPage() const;
    void createBsfTabs(QWidget *parent);

public slots:
    void onChangeTab(int index);

private:
    QHBoxLayout *hbox = nullptr;
    QWidget *ioDevicePage = nullptr;
    QWidget *arduinoPage = nullptr;
    QWidget *controlPanelPage = nullptr;
    QWidget *recipePage = nullptr;
    QWidget *logPage = nullptr;
    QWidget *statemachineTab = nullptr;
    //QWidget *parentWidget = nullptr;
    QTabWidget * mainTabBar = nullptr;
    const QString tabNames[5] = {"I/O Apparaten", "Arduino's", "Recepten", "Logs", "State Machine"};

    void createIODevicePage();
    void createArduinoPage();
    void createRecipePage();
    void createLogPage();
    void createStatemachinePage();

};
#endif //BSF_TABCONTROLLER_H
