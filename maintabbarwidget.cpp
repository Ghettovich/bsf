#include "maintabbarwidget.h"

#include <QSortFilterProxyModel>
#include <QtWidgets>

MainTabBarWidget::MainTabBarWidget(QWidget *parent)
    : QTabWidget (parent),
      logTable(new LogTableModel(this))
{
    // ToDo wire up events        
    setupTabs();
}

void MainTabBarWidget::setupTabs()
{
//    arduinoTab = new ArduinoTab(this);
//    addTab(arduinoTab, tr("Arduino's"));
//    ioDeviceTab = new IODeviceTab(this);
//    addTab(ioDeviceTab, tr("I/O Apparaten"));
    recipeTab = new RecipeTab(this);
    addTab(recipeTab, tr("Recepten"));

    tableView = new QTableView(this);
    tableView->setModel(logTable);
    tableView->setMinimumSize(1596, 764);
    tableView->show();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    addTab(tableView, "Logs");

    addEntry("sample", "entry");
    addEntry("sample", "entry");
    addEntry("sample", "entry");

    //logTab = new LogTab(this);



    //addTab(logTab, tr("Logs"));
    // Set arduino tab as current
    //setCurrentWidget(arduinoTab);
}

void MainTabBarWidget::currentChanged(int index)
{
    switch (index) {
        case 0:
            setCurrentWidget(arduinoTab);
        break;
        case 1 :
            setCurrentWidget(ioDeviceTab);
        break;
        case 2 :
            setCurrentWidget(recipeTab);
        break;
        case 3 :
            setCurrentWidget(logTab);
        break;
        default:
            setStatusTip(tr("Tab niet gevonden"));
        break;

    }
    addTab(new RecipeTab(this), tr("oneMore"));
}

void MainTabBarWidget::addEntry(const QString &title, const QString &msg)
{
    if (!logTable->getLogs().contains({ title, msg })) {
        logTable->insertRows(0, 1, QModelIndex());

        QModelIndex index = logTable->index(0, 0, QModelIndex());
        logTable->setData(index, title, Qt::EditRole);
        index = logTable->index(0, 1);
        logTable->setData(index, msg, Qt::EditRole);
    } else {
        QMessageBox::information(this, tr("Duplicate Name"),
            tr("The name \"%1\" already exists.").arg(title));
    }
}
