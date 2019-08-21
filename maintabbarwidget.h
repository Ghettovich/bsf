#ifndef LOGTABLEWIDGET_H
#define LOGTABLEWIDGET_H

#include "headers/models/logtablemodel.h"
#include "headers/tabs/main/logtab.h"
#include "headers/tabs/main/arduinotab.h"
#include "headers/tabs/main/recipetab.h"
#include "headers/tabs/main/iodevicetab.h"
#include <QItemSelection>
#include <QStatusBar>
#include <QTabWidget>

class QTabWidget;

class MainTabBarWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainTabBarWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &filename);
    void writeToFile(const QString &filename);
    virtual void currentChanged(int index);

public slots:

private slots:
    //void updateMainStatusBar(const QString &msg);

private:
    void setupTabs();

    ArduinoTab *arduinoTab;
    IODeviceTab *ioDeviceTab;
    RecipeTab *recipeTab;
    LogTab *logTab;

protected:

};

#endif // LOGTABLEWIDGET_H
