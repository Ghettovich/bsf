#include "incl/ui/tabs/logtab.h"
#include <QAction>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableView>
#include <QWidget>
#include <incl/ui/mainwindow.h>

LogTab::LogTab(QTabWidget *parent)
    : QWidget(parent),
      logTable(new LogTableModel(this))
{
    setStatusTip(statusBarMsg);
    createTableView();
    createSampleData();
}

void LogTab::createTableView()
{
    tableView = new QTableView(this);
    tableView->setModel(logTable);
    //tableView->setMinimumSize(1596, 764);
    tableView->show();
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);
}

void LogTab::createSampleData()
{
    addEntry("3", "ssda", "error", "asd");
    addEntry("2", "durp", "warning", "asdentry");
    addEntry("1", "sample", "info", "entry");
}

void LogTab::addEntry(const QString &id, const QString &title, const QString &severity, const QString &msg)
{
    logTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = logTable->index(0, 0, QModelIndex());
    logTable->setData(index, id, Qt::EditRole);
    index = logTable->index(0, 1);
    logTable->setData(index, title, Qt::EditRole);
    index = logTable->index(0, 2);
    logTable->setData(index, severity, Qt::EditRole);
    index = logTable->index(0, 3);
    logTable->setData(index, msg, Qt::EditRole);

}
