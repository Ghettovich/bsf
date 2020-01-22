#ifndef BSF_LOGTAB_H
#define BSF_LOGTAB_H

#include <domain/bafalog.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTableWidget>


class LogTab : public QWidget
{
    Q_OBJECT

public:
    LogTab(QWidget *widget, const Qt::WindowFlags &f);

private:
    QStringList logTypes = QStringList() << "Error" << "Warning" << "Info";
    QTableWidget *tableViewBsfLogs = nullptr;
    QString convertIODeviceTypeToString(BafaLog::LOG_SEVERITY);

    const QString statusBarMsg = "Log tab actief";
    void createTableView();
};

#endif // BSF_LOGTAB_H
