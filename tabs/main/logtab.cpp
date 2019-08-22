#include "headers/tabs/main/logtab.h"
#include <QAction>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableView>
#include <QWidget>
#include <mainwindow.h>

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
    tableView->setMinimumSize(1596, 764);
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
    addEntry("sample", "entry");
    addEntry("durp", "asdentry");
    addEntry("ssda", "asd");
}

void LogTab::addEntry(const QString &title, const QString &msg)
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
