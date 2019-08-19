#include "headers/tabs/main/logtab.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableView>
#include <QWidget>
#include <qsortfilterproxymodel.h>

LogTab::LogTab(QWidget *parent)
    : QTabWidget(parent),
      logTable(new LogTableModel)
{    
    createTableView();
    createSampleData();
}

void LogTab::createTableView()
{
    // To Do create columns from constants
    const auto regExp = QRegularExpression(QString("^[%1].*").arg("Logs"),
                                           QRegularExpression::CaseInsensitiveOption);

    auto proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(logTable);
    proxyModel->setFilterRegularExpression(regExp);
    proxyModel->setFilterKeyColumn(0);

    QTableView *tableView = new QTableView(this);
    tableView->setMinimumSize(1596, 764);
    tableView->show();

    tableView->setModel(proxyModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &LogTab::selectionChanged);

    connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
        if (widget(tabIndex) == tableView)
            emit selectionChanged(tableView->selectionModel()->selection());
    });
}

void LogTab::createSampleData()
{
    logTable->insertRows(0, 1, QModelIndex());

    QModelIndex index = logTable->index(0, 0, QModelIndex());
    logTable->data(index, Qt::DisplayRole);
    logTable->setData(index, "Hoi");
    index = logTable->index(0, 1, QModelIndex());
    logTable->setData(index, "address");

    //removeTab(indexOf(newAddressTab));
}
