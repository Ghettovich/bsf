#ifndef BSF_LOGREPO_H
#define BSF_LOGREPO_H

#include <domain/bafalog.h>
#include <QtCore/QVector>
#include <QtSql/QSqlDatabase>

class LogRepository {

public:
    LogRepository();
    QVector<BafaLog> createBsfLogList();
    void addLog(BafaLog);
    void addLog(const QString &logMsg, int logSeverity);

private:
    void insert(BafaLog);
    void setDefaultDatabase(QSqlDatabase&);
};
#endif //BSF_LOGREPO_H
