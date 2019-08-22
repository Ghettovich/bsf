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

    QString title() const;
    QString msg() const;

public slots:

private:
    const QString statusBarMsg = "Log tab actief";

};

#endif // LOGTAB_H
