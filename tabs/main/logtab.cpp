#include "headers/tabs/main/logtab.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableView>
#include <QWidget>
#include <qsortfilterproxymodel.h>

LogTab::LogTab(QWidget *parent)
    : QTabWidget(parent),
      logTable(new LogTableModel(this))
{
    createTableView();
    createSampleData();
}

void LogTab::createTableView()
{
    // To Do create columns from constants
    const auto regExp = QRegularExpression(QString("^[%1].*").arg("Logs"),
                                           QRegularExpression::CaseInsensitiveOption);

    auto proxyModel = new QSortFilterProxyModel(logTable);
    proxyModel->setSourceModel(logTable);
    proxyModel->setFilterRegularExpression(regExp);
    proxyModel->setFilterKeyColumn(0);

    QTableView *tableView = new QTableView(this);
    tableView->setMinimumSize(1596, 764);
    tableView->show();

    tableView->setModel(logTable);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    logTable->insertRows(0, 10, QModelIndex());

    QModelIndex index = logTable->index(0, 0, QModelIndex());
    logTable->setData(index, "waarschuwing");
    index = logTable->index(0, 1, QModelIndex());

    logTable->setData(index, "niet bereikbaar");
    index = logTable->index(0, 2, QModelIndex());
    logTable->setData(index, "1");
}

void LogTab::createSampleData()
{

}
