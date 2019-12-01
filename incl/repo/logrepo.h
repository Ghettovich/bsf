#ifndef BSF_LOGREPO_H
#define BSF_LOGREPO_H

#include <QtSql/QSqlDatabase>
#include <incl/data/bsfdatabaseconfig.h>
#include <incl/domain/log.h>

class LogRepository {
public:
    explicit LogRepository();
    QList<BsfLog> *getBsfLogs();
    void addLog(const BsfLog &log);
    void addLog(const QString &logMsg, LogSeverity logSeverity);


private:
    BsfDbconfig *bsfDbConfig = nullptr;
    QSqlDatabase getQSqlDatabase();
    void insert(BsfLog log);
};
#endif //BSF_LOGREPO_H
