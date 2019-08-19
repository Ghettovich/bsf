#ifndef LOGTAB_H
#define LOGTAB_H
#include "logmodel.h"

#include <QTabWidget>
#include <QWidget>

class LogTab : public QTabWidget
{
    Q_OBJECT

public:
    LogTab(QTabWidget *parent = nullptr);

private:
    LogTableModel *logTable;

};

#endif // LOGTAB_H
