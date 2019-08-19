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

class LogTab : public QTabWidget
{
    Q_OBJECT

public:
    LogTab(QTabWidget *parent = nullptr);    

private:
    LogTableModel *logTable;
    void createTableView();
};

#endif // LOGTAB_H
