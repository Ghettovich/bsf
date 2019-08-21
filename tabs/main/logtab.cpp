#include "headers/tabs/main/logtab.h"
#include <QAction>
#include <QHeaderView>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableView>
#include <QWidget>
#include <mainwindow.h>
#include <qsortfilterproxymodel.h>

LogTab::LogTab(QTabWidget *parent)
    : QWidget(parent),
      tableView(new QTableView(this))
{

    //tableView = new QTableView(this);
    tableView->setModel(&logTable);
    setStatusTip(statusBarMsg);
    createTableView();
    createSampleData();

}

void LogTab::createTableView()
{
    // To Do create columns from constants
    const auto regExp = QRegularExpression(QString("^[%1].*").arg("Logs"),
                                           QRegularExpression::CaseInsensitiveOption);

    auto proxyModel = new QSortFilterProxyModel(&logTable);
    proxyModel->setSourceModel(&logTable);
    proxyModel->setFilterRegularExpression(regExp);
    proxyModel->setFilterKeyColumn(0);

    //tableView = new QTableView(this);
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
    //logTable.insertRows(0, 1, QModelIndex());

    QModelIndex index = logTable.index(0, 0);
    logTable.setData(index, tr("Hey!"));
    index = logTable.index(0, 1);
    logTable.setData(index, tr("Listen!? Please *_*?"));



//    index = logTable.index(0, 2, QModelIndex());
//    logTable.setData(index, "High Prio");
}

