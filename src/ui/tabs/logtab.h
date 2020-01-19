#ifndef LOGTAB_H
#define LOGTAB_H

#include <QtWidgets/QWidget>
#include <QTableWidget>
#include <domain/log.h>


class LogTab : public QWidget
{
    Q_OBJECT

public:
    explicit LogTab();

public slots:

private:
    QList<BsfLog> * bsfLogList;
    QStringList logTypes = QStringList() << "Error" << "Warning" << "Info";
    QTableWidget *tableViewBsfLogs = nullptr;

    QString convertIODeviceTypeToString(int _ioDeviceType);

    const QString statusBarMsg = "Log tab actief";
    void createTableView();
};

#endif // LOGTAB_H
