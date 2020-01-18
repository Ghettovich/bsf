#ifndef BSF_LOGREPO_H
#define BSF_LOGREPO_H

#include <QtSql/QSqlDatabase>
#include <data/bsfdatabaseconfig.h>
#include <domain/log.h>

class LogRepository {
public:
    explicit LogRepository();
    QList<BsfLog> *getBsfLogs();
    void addLog(const BsfLog &log);
    void addLog(const QString &logMsg, LogSeverity logSeverity);


private:
    BsfDbconfig bsfDbConfig;
    QSqlDatabase getQSqlDatabase();
    void insert(BsfLog log);
};
#endif //BSF_LOGREPO_H
