#include "logtab.h"
#include <QRegularExpression>
#include <QTableView>
#include <QWidget>
#include <qsortfilterproxymodel.h>



LogTab::LogTab(QTabWidget *parent)
    : QTabWidget(parent),
      logTable(new LogTableModel(this))
{
    //move(5, 52);
    // To Do create columns from constants
//    const auto regExp = QRegularExpression(QString("^[%1].*").arg("Logs"),
//                                           QRegularExpression::CaseInsensitiveOption);

//    auto proxyModel = new QSortFilterProxyModel(this);
//    proxyModel->setSourceModel(logTable);
//    proxyModel->setFilterRegularExpression(regExp);
//    proxyModel->setFilterKeyColumn(0);

//    QTableView *tableView = new QTableView;
//    tableView->setModel(proxyModel);
//    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    tableView->horizontalHeader
//    tableView->horizontalHeader->setStretchLastSection(true);
//    tableView->verticalHeader()->hide();
//    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
//    tableView->setSortingEnabled(true);

    /* ToDo: Wire up events  */
//    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
//            this, &MainTabBarWidget::selectionChanged);

//    connect(this, &QTabWidget::currentChanged, this, [this, tableView](int tabIndex) {
//        if (widget(tabIndex) == tableView)
//            emit selectionChanged(tableView->selectionModel()->selection());
//    });

      //addTab(tableView, "Logs");
}
