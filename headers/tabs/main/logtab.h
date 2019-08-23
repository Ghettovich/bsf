#ifndef LOGTAB_H
#define LOGTAB_H
#include "headers/models/logtablemodel.h"

#include <QTabWidget>
#include <QTableView>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QItemSelectModel;
QT_END_NAMESPACE

class LogTab : public QWidget
{
    Q_OBJECT

public:
    LogTab(QTabWidget *parent = nullptr);
    void createSampleData();

public slots:

private:
    QTableView *tableView;
    LogTableModel *logTable;
    const QString statusBarMsg = "Log tab actief";

    void createTableView();

    void addEntry(const QString &id, const QString &title, const QString &severity, const QString &msg);

};

#endif // LOGTAB_H
