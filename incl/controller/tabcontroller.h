#ifndef BSF_TABCONTROLLER_H
#define BSF_TABCONTROLLER_H

#include <QtCore/QObject>
#include <incl/ui/widgets/maintabbarwidget.h>

class TabController : public QObject {

public:
    explicit TabController(QWidget *_parent = nullptr);
    MainTabBarWidget *getMainTabbarWidget() const;
    void createBsfTabs();

private:
    QList<QWidget *> tabList;
    QWidget *parentWidget = nullptr;
    MainTabBarWidget *mainTabbarWidget = nullptr;
    const QString tabNames[5] = {"I/O Apparaten", "Arduino's","Control (test) paneel", "Recepten", "Logs"};
};
#endif //BSF_TABCONTROLLER_H
