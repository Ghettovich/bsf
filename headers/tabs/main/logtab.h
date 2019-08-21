#ifndef LOGTAB_H
#define LOGTAB_H
#include "headers/models/logtablemodel.h"

#include <QTabWidget>
#include <QTableView>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectModel;
QT_END_NAMESPACE

class LogTab : public QWidget
{
    Q_OBJECT

public:
    LogTab(QTabWidget *parent = nullptr);
    //LogTab(QTabWidget *parent = nullptr, QTableView *tableView = nullptr);

public slots:

private:
    const QString statusBarMsg = "Log tab actief";

    LogTableModel logTable;
    // Methods
    void createTableView();
    void createSampleData();

    // QT widgets
    QTableView *tableView;
    // Models & resources
    //LogTableModel *logTable;

};

#endif // LOGTAB_H
