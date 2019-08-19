#ifndef LOGTABLEWIDGET_H
#define LOGTABLEWIDGET_H

#include "headers/models/logtablemodel.h"
#include "headers/tabs/main/logtab.h"
#include "headers/tabs/main/arduinotab.h"
#include "headers/tabs/main/recipetab.h"
#include "headers/tabs/main/iodevicetab.h"
#include <QItemSelection>
#include <QTabWidget>


class MainTabBarWidget : public QTabWidget
{
    Q_OBJECT

public:
    MainTabBarWidget(QWidget *parent = nullptr);
    void readFromFile(const QString &filename);
    void writeToFile(const QString &filename);

public slots:

signals:
    void selectionChanged(const QItemSelection &selected);

private:
    void setupTabs();

    //LogTableModel *logTable;
    LogTab *logTab;
    ArduinoTab *arduinoTab;
    RecipeTab *recipeTab;
    IODeviceTab *ioDeviceTab;
};

#endif // LOGTABLEWIDGET_H
