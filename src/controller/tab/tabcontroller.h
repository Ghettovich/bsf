#ifndef BSF_TABCONTROLLER_H
#define BSF_TABCONTROLLER_H

#include <QtCore/QObject>
#include <ui/widgets/maintabbarwidget.h>

class TabController : public QObject {

    Q_OBJECT

public:
    explicit TabController(QWidget *_parent = nullptr);
    MainTabBarWidget *getMainTabbarWidget() const;
    void createBsfTabs();

public slots:
    void onChangeTab(int index);

private:
    QList<QWidget *> tabList;
    QWidget *parentWidget = nullptr;
    MainTabBarWidget *mainTabbarWidget = nullptr;
    const QString tabNames[6] = {"I/O Apparaten", "Arduino's","Control (test) paneel", "Recepten", "Logs", "State Machine"};
};
#endif //BSF_TABCONTROLLER_H
