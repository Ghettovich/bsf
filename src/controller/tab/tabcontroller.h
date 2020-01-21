#ifndef BSF_TABCONTROLLER_H
#define BSF_TABCONTROLLER_H

#include <QObject>
#include <QString>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>

class TabController : public QObject {

    Q_OBJECT

public:
    explicit TabController(QWidget *parent);
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
    QTabWidget * mainTabBar = nullptr;
    const QString tabNames[5] = {"I/O Apparaten", "Arduino's", "Recepten", "Logs", "State Machine"};

    void createIODevicePage();
    void createArduinoPage();
    void createRecipePage();
    void createLogPage();
//    void createStatemachinePage();

};
#endif //BSF_TABCONTROLLER_H
