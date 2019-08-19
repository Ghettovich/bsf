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
    LogTab(QWidget *parent = nullptr);

signals:
    void selectionChanged (const QItemSelection &selected);

private:
    void createTableView();
    void createSampleData();

    LogTableModel *logTable;
};

#endif // LOGTAB_H
